#pragma once

#include <fstream>
#include <list>
#include <vector>

class Token;

class Lexer {
 public:
  Lexer();
  ~Lexer();

 public:
  bool run();
  std::list<Token*> getTokens();

 private:
  bool isBlank();

 private:
  size_t index_;
  std::vector<char> buffer_;
  std::ifstream fileInput_;
  std::list<Token*> tokens_;
};