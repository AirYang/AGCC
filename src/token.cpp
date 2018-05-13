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

static inline const char* tokenTypeToStr(enum TokenType tk) {
#define TOKENTYPE_TO_STR(x) \
  case x:                   \
    return (#x);
  switch (tk) {
    TOKENTYPE_TO_STR(TokenType::KEY_WORD)
    TOKENTYPE_TO_STR(TokenType::IDENTIFIER)
    TOKENTYPE_TO_STR(TokenType::DIGIT_CONSTANT)
    TOKENTYPE_TO_STR(TokenType::OPERATOR)
    TOKENTYPE_TO_STR(TokenType::SEPARATOR)
    TOKENTYPE_TO_STR(TokenType::STRING_CONSTANT)
    TOKENTYPE_TO_STR(TokenType::INCLUDE)
    TOKENTYPE_TO_STR(TokenType::INT)
    TOKENTYPE_TO_STR(TokenType::FLOAT)
    TOKENTYPE_TO_STR(TokenType::CHAR)
    TOKENTYPE_TO_STR(TokenType::DOUBLE)
    TOKENTYPE_TO_STR(TokenType::FOR)
    TOKENTYPE_TO_STR(TokenType::IF)
    TOKENTYPE_TO_STR(TokenType::ELSE)
    TOKENTYPE_TO_STR(TokenType::WHILE)
    TOKENTYPE_TO_STR(TokenType::DO)
    TOKENTYPE_TO_STR(TokenType::RETURN)
    TOKENTYPE_TO_STR(TokenType::ASSIGN)
    TOKENTYPE_TO_STR(TokenType::ADDRESS)
    TOKENTYPE_TO_STR(TokenType::LT)
    TOKENTYPE_TO_STR(TokenType::GT)
    TOKENTYPE_TO_STR(TokenType::SELF_PLUS)
    TOKENTYPE_TO_STR(TokenType::SELF_MINUS)
    TOKENTYPE_TO_STR(TokenType::PLUS)
    TOKENTYPE_TO_STR(TokenType::MINUS)
    TOKENTYPE_TO_STR(TokenType::MUL)
    TOKENTYPE_TO_STR(TokenType::DIV)
    TOKENTYPE_TO_STR(TokenType::GET)
    TOKENTYPE_TO_STR(TokenType::LET)
    TOKENTYPE_TO_STR(TokenType::LL_BRACKET)
    TOKENTYPE_TO_STR(TokenType::RL_BRACKET)
    TOKENTYPE_TO_STR(TokenType::LB_BRACKET)
    TOKENTYPE_TO_STR(TokenType::RB_BRACKET)
    TOKENTYPE_TO_STR(TokenType::LM_BRACKET)
    TOKENTYPE_TO_STR(TokenType::RM_BRACKET)
    TOKENTYPE_TO_STR(TokenType::COMMA)
    TOKENTYPE_TO_STR(TokenType::DOUBLE_QUOTE)
    TOKENTYPE_TO_STR(TokenType::SEMICOLON)
    TOKENTYPE_TO_STR(TokenType::SHARP)
    TOKENTYPE_TO_STR(TokenType::NOT_A_TYPE)
  }
#undef TOKENTYPE_TO_STR
  return "Unsupported Token Type";
}

std::string Token::toString() const {
  return std::string("TokenType[") + std::string(tokenTypeToStr(type_)) +
         std::string("] Value[") + value_ + std::string("]");
}

bool Token::isKeyWord(const std::string& value) {
  return ((dataKeyWord_.find(value) != dataKeyWord_.end()) ||
          (controlKeyWord_.find(value) != controlKeyWord_.end()) ||
          (macroKeyWord_.find(value) != macroKeyWord_.end()) ||
          (funcKeyWord_.find(value) != funcKeyWord_.end()));
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