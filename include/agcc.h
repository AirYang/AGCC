#pragma once

#include <fstream>
#include <string>

class SyntaxTree;
class SyntaxTreeNode;

class AGCC {
 public:
  AGCC(int argc, char** argv);

 public:
  bool run();

 private:
  void help();
  bool paraInit(int argc, char** argv);
  void printSyntaxTree(SyntaxTree* tree);
  void printSyntaxTreeNode(SyntaxTreeNode* node);

 private:
  std::string fileName_;
  std::ifstream fileInput_;
  bool needLexer_;
  bool needParser_;
  bool needAssembler_;
};