#pragma once

#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "../include/syntax_tree.h"
#include "../include/type.h"

class AssemblerFileHandler {
 public:
  AssemblerFileHandler();

 public:
  void insert(const std::string& value, SegmentType type);
  bool saveToFile(const std::string& fileName);

 private:
  size_t dataIndex_;
  size_t bssIndex_;
  size_t textIndex_;
  std::vector<std::string> buffer_;
};

class Assembler {
 public:
  Assembler(const SyntaxTree* tree);

 public:
  bool saveToFile(const std::string& fileName);

 private:
  void traverse(const SyntaxTreeNode* node = nullptr);
  void handlerBlock(const SyntaxTreeNode* node = nullptr);
  void doInclude(const SyntaxTreeNode* node = nullptr);
  void doFunctionStatement(const SyntaxTreeNode* node = nullptr);
  void doStatement(const SyntaxTreeNode* node = nullptr);
  void doFunctionCall(const SyntaxTreeNode* node = nullptr);
  void doAssignment(const SyntaxTreeNode* node = nullptr);
  void doControlIf(const SyntaxTreeNode* node = nullptr);
  void doControlFor(const SyntaxTreeNode* node = nullptr);
  void doControlWhile(const SyntaxTreeNode* node = nullptr);
  std::unordered_map<std::string, std::string> doExpression(
      const SyntaxTreeNode* node = nullptr);
  void doReturn(const SyntaxTreeNode* node = nullptr);
  void doTraverseExpression(const SyntaxTreeNode* node = nullptr);
  bool judgeContainFloat(
      const std::unordered_map<std::string, std::string>& opA,
      const std::unordered_map<std::string, std::string>& opB);
  bool judgeIsFloat(const std::unordered_map<std::string, std::string>& opA);
  std::string doSizeof(const std::string type);

 private:
  size_t labelCount_;
  const SyntaxTree* tree_;
  AssemblerFileHandler assFileHandler_;
  std::stack<std::string> operatorStack_;
  std::vector<std::unordered_map<std::string, std::string>> operandStack_;
  std::unordered_map<std::string, std::string> labelsIfElse_;
  std::unordered_map<std::string, std::unordered_map<std::string, std::string>>
      symbolTable_;

 private:
  static const std::unordered_set<std::string> sentenceType_;
};