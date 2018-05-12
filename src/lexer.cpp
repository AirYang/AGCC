#include <cctype>
#include <cstdio>

#include <algorithm>

#include "../include/error.h"
#include "../include/lexer.h"
#include "../include/token.h"

// const std::set<char> Lexer::blankSet_{' ', '\t', '\n', '\r'};

Lexer::Lexer(std::ifstream& fileInput)
    : index_(0), buffer_(), fileInput_(fileInput), tokens_() {
  bufferInit();
}

Lexer::~Lexer() {
  std::for_each(tokens_.begin(), tokens_.end(), [](Token* tk) { delete tk; });
}

void Lexer::bufferInit() {
  char c;
  while (fileInput_.get(c)) {
    buffer_.push_back(c);
  }
}

bool Lexer::isBlank(size_t index) {
  if (index >= buffer_.size()) {
    error(__FILE__, __FUNCTION__, __LINE__);
  }

  return Token::isBlank(buffer_[index]);
}

void Lexer::skipBlank() {
  while ((index_ < buffer_.size()) && isBlank(index_)) {
    ++index_;
  }
}

// bool Lexer::isKeyWord(const std::string& value) { return; }

std::list<Token*> Lexer::getTokens() {
  for (skipBlank(); index_ < buffer_.size(); skipBlank()) {
    if (buffer_[index_] == '#') {
      tokens_.push_back(
          new Token(TokenType::SEPARATOR, std::string(1, buffer_[index_])));
      ++index_;
      skipBlank();

      while (index_ < buffer_.size()) {
        if (std::string(buffer_.begin() + index_, buffer_.begin() + index_ + 7)
                .compare("include") == 0) {
          tokens_.push_back(new Token(TokenType::KEY_WORD, "include"));
          index_ += 7;
          skipBlank();
        } else if ((buffer_[index_] == '\"') || (buffer_[index_] == '<')) {
          tokens_.push_back(
              new Token(TokenType::SEPARATOR, std::string(1, buffer_[index_])));

          // need debug
          std::string closeFlag;
          if (buffer_[index_] == '\"') {
            closeFlag = "\"";
          } else {
            closeFlag = ">";
          }

          index_++;
          skipBlank();

          std::string includePath;
          while (buffer_[index_] != closeFlag[0]) {
            includePath = includePath + std::string(1, buffer_[index_]);
            index_++;
          }
          tokens_.push_back(new Token(TokenType::IDENTIFIER, includePath));
          tokens_.push_back(new Token(TokenType::SEPARATOR, closeFlag));

          index_++;
          skipBlank();
          break;
        } else {
          error(__FILE__, __FUNCTION__, __LINE__);
        }
      }
    } else if (isdigit(buffer_[index_])) {
      std::string temp = "";
      while (index_ < buffer_.size()) {
        if ((isdigit(buffer_[index_])) ||
            ((buffer_[index_] == '.') && (isdigit(buffer_[index_ + 1])))) {
          temp += std::string(1, buffer_[index_]);
          ++index_;
        } else if (!isdigit(buffer_[index_])) {
          if (buffer_[index_] == '.') {
#ifdef DEBUG
            perror("float number error!\n");
#endif  // DEBUG
            error(__FILE__, __FUNCTION__, __LINE__);
          } else {
            break;
          }
        }
      }

      tokens_.push_back(new Token(TokenType::DIGIT_CONSTANT, temp));
      skipBlank();
    } else if (isalpha(buffer_[index_]) || (buffer_[index_] == '_')) {
      std::string temp = "";
      while ((index_ < buffer_.size()) &&
             (isalpha(buffer_[index_]) || isdigit(buffer_[index_]) ||
              (buffer_[index_] == '_'))) {
        temp += std::string(1, buffer_[index_]);
        ++index_;
      }

      if (Token::isKeyWord(temp)) {
        tokens_.push_back(new Token(TokenType::KEY_WORD, temp));
      } else {
        tokens_.push_back(new Token(TokenType::IDENTIFIER, temp));
      }
      skipBlank();
    } else if (Token::isDelimiter(buffer_[index_])) {
      tokens_.push_back(
          new Token(TokenType::SEPARATOR, std::string(1, buffer_[index_])));

      if (buffer_[index_] == '\"') {
        ++index_;
        std::string temp = "";
        while (index_ < buffer_.size()) {
          if (buffer_[index_] != '\"') {
            temp += std::string(1, buffer_[index_]);
            ++index_;
          } else {
            break;
          }
        }

        if (buffer_[index_] != '\"') {
#ifdef DEBUG
          perror("string lack \"");
#endif  // DEBUG
          error(__FILE__, __FUNCTION__, __LINE__);
        }

        tokens_.push_back(new Token(TokenType::STRING_CONSTANT, temp));
        tokens_.push_back(
            new Token(TokenType::SEPARATOR, std::string(1, '\"')));
      }

      ++index_;
      skipBlank();
    } else if (Token::isOperator(buffer_[index_])) {
      if (((buffer_[index_] == '-') || (buffer_[index_] == '+')) &&
          (buffer_[index_ + 1] == buffer_[index_])) {
        tokens_.push_back(
            new Token(TokenType::OPERATOR, std::string(2, buffer_[index_])));
        index_ += 2;
        skipBlank();
      } else if (((buffer_[index_] == '<') || (buffer_[index_] == '>')) &&
                 (buffer_[index_ + 1] == '=')) {
        tokens_.push_back(
            new Token(TokenType::OPERATOR,
                      std::string(1, buffer_[index_]) + std::string(1, '=')));
        index_ += 2;
        skipBlank();
      } else {
        tokens_.push_back(
            new Token(TokenType::OPERATOR, std::string(1, buffer_[index_])));
        ++index_;
        skipBlank();
      }
    }
#ifdef DEBUG
    else {
      printf("Un lex char[%c]\n", buffer_[index_]);
    }
#endif  // DEBUG
  }
  return tokens_;
}