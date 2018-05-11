#pragma once

#include <string>
#include <unordered_map>

#include "../include/type.h"

class Token {
 public:
  Token(const TokenType& type, const std::string& value);

 private:
  TokenType type_;
  std::string value_;

 private:
  static const std::unordered_map<std::string, TokenType> vtkMap_;
};