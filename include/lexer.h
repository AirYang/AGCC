#pragma once

#include <fstream>
#include <list>
#include <unordered_set>
#include <vector>

class Token;

class Lexer {
 public:
  Lexer(std::ifstream& fileInput);
  ~Lexer();

 public:
  // bool run();
  std::list<Token*> getTokens();

 private:
  void bufferInit();
  bool isBlank(size_t index);
  void skipBlank();
  // bool isKeyWord(const std::string& value);

 private:
  size_t index_;
  std::vector<char> buffer_;
  std::ifstream& fileInput_;
  std::list<Token*> tokens_;

 private:
  // static const std::unordered_set<char> blankSet_;
};