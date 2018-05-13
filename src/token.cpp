#include "../include/token.h"
#include "../include/error.h"

const std::unordered_map<std::string, TokenType> Token::vtkMap_{
    {"include", TokenType::INCLUDE},
    {"int", TokenType::INT},
    {"float", TokenType::FLOAT},
    {"char", TokenType::CHAR},
    {"double", TokenType::DOUBLE},
    {"for", TokenType::FOR},
    {"if", TokenType::IF},
    {"else", TokenType::ELSE},
    {"while", TokenType::WHILE},
    {"do", TokenType::DO},
    {"return", TokenType::RETURN},
    {"=", TokenType::ASSIGN},
    {"&", TokenType::ADDRESS},
    {"<", TokenType::LT},
    {">", TokenType::GT},
    {"++", TokenType::SELF_PLUS},
    {"--", TokenType::SELF_MINUS},
    {"+", TokenType::PLUS},
    {"-", TokenType::MINUS},
    {"*", TokenType::MUL},
    {"/", TokenType::DIV},
    {">=", TokenType::GET},
    {"<=", TokenType::LET},
    {"(", TokenType::LL_BRACKET},
    {")", TokenType::RL_BRACKET},
    {"{", TokenType::LB_BRACKET},
    {"}", TokenType::RB_BRACKET},
    {"[", TokenType::LM_BRACKET},
    {"]", TokenType::RM_BRACKET},
    {",", TokenType::COMMA},
    {"\"", TokenType::DOUBLE_QUOTE},
    {";", TokenType::SEMICOLON},
    {"#", TokenType::SHARP}};

const std::unordered_set<char> Token::blankSet_{' ', '\t', '\n', '\r'};

// ['(', ')', '{', '}', '[', ']', ',', '\"', ';']
const std::unordered_set<char> Token::delimiterSet_{'(', ')', '{',  '}', '[',
                                                    ']', ',', '\"', ';'};

// [ '=', '&', '<', '>', '++', '--', '+', '-', '*', '/', '>=', '<=', '!=' ]
const std::unordered_set<char> Token::operatorSet_{
    '=', '&', '<', '>', '+', '-', '+', '-', '*', '/', '>', '<', '!'};

const std::unordered_set<std::string> Token::dataKeyWord_{
    "int", "float", "char", "double", "void"};

const std::unordered_set<std::string> Token::controlKeyWord_{
    "for", "if", "else", "while", "do"};

const std::unordered_set<std::string> Token::macroKeyWord_{"include"};

const std::unordered_set<std::string> Token::funcKeyWord_{"return"};

Token::Token(const TokenType& type, const std::string& value)
    : type_(type), value_(value) {
  if (type_ == TokenType::KEY_WORD || type_ == TokenType::OPERATOR ||
      type_ == TokenType::SEPARATOR) {
    auto result = vtkMap_.find(value_);
    if (result != vtkMap_.end()) {
      type_ = result->second;
    } else {
      error(__FILE__, __FUNCTION__, __LINE__);
    }
  }
}

Token::~Token() {}

std::string Token::toString() const {
  return std::string("TokenType[") + std::string(tokenTypeToStr(type_)) +
         std::string("] Value[") + value_ + std::string("]");
}

std::string Token::getValue() const { return value_; }

TokenType Token::getType() const { return type_; }

bool Token::isKeyWord(const std::string& value) {
  return ((dataKeyWord_.find(value) != dataKeyWord_.end()) ||
          (controlKeyWord_.find(value) != controlKeyWord_.end()) ||
          (macroKeyWord_.find(value) != macroKeyWord_.end()) ||
          (funcKeyWord_.find(value) != funcKeyWord_.end()));
}

bool Token::isControlKeyWord(const std::string& value) {
  return controlKeyWord_.find(value) != controlKeyWord_.end();
}

bool Token::isDataKeyWord(const std::string& value) {
  return dataKeyWord_.find(value) != dataKeyWord_.end();
}

bool Token::isFuncKeyWord(const std::string& value) {
  return funcKeyWord_.find(value) != funcKeyWord_.end();
}

bool Token::isBlank(const char& value) {
  return (blankSet_.find(value) != blankSet_.end());
}

bool Token::isDelimiter(const char& value) {
  return (delimiterSet_.find(value) != delimiterSet_.end());
}

bool Token::isOperator(const char& value) {
  return (operatorSet_.find(value) != operatorSet_.end());
}