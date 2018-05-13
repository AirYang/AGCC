#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>

#include "../include/type.h"

class Token {
 public:
  Token(const TokenType& type, const std::string& value);
  ~Token();

 public:
  std::string toString() const;
  std::string getValue() const;
  TokenType getType() const;

 public:
  static bool isKeyWord(const std::string& value);
  static bool isControlKeyWord(const std::string& value);
  static bool isDataKeyWord(const std::string& value);
  static bool isFuncKeyWord(const std::string& value);
  static bool isBlank(const char& value);
  static bool isDelimiter(const char& value);
  static bool isOperator(const char& value);

 private:
  TokenType type_;
  std::string value_;

 private:
  static const std::unordered_map<std::string, TokenType> vtkMap_;
  static const std::unordered_set<char> blankSet_;
  static const std::unordered_set<char> delimiterSet_;
  static const std::unordered_set<char> operatorSet_;
  static const std::unordered_set<std::string> dataKeyWord_;
  static const std::unordered_set<std::string> controlKeyWord_;
  static const std::unordered_set<std::string> macroKeyWord_;
  static const std::unordered_set<std::string> funcKeyWord_;
};