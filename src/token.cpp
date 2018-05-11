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