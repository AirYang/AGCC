#pragma once

#include <fstream>
#include <string>

class AGCC {
 public:
  AGCC(int argc, char** argv);

 public:
  bool run();

 private:
  void help();
  bool paraInit(int argc, char** argv);

 private:
  std::string fileName_;
  std::ifstream fileInput_;
  bool needLexer_;
  bool needParser_;
  bool needAssembler_;
};