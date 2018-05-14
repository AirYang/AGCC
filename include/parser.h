#pragma once

#include <list>

#include "../include/syntax_tree.h"
#include "../include/token.h"
#include "../include/type.h"

class Parser {
 public:
  Parser(const std::list<Token*>& tokens);
  ~Parser();

 public:
  SyntaxTree* getSyntaxTree();

 private:
  SentencePattern judgeSentencePattern();
  void doInclude(SyntaxTreeNode* father = nullptr);
  void doFunctionStatement(SyntaxTreeNode* father = nullptr);
  void doBlock(SyntaxTree* fatherTree);
  void doStatement(SyntaxTreeNode* father = nullptr);
  void doAssignment(SyntaxTreeNode* father = nullptr);
  void doFunctionCall(SyntaxTreeNode* father = nullptr);
  void doControl(SyntaxTreeNode* father = nullptr);
  void doReturn(SyntaxTreeNode* father = nullptr);
  void doExpression(std::list<Token*>::const_iterator citEnd,
                    SyntaxTreeNode* father = nullptr);
  void doWhile(SyntaxTreeNode* father = nullptr);
  void doIfElse(SyntaxTreeNode* father = nullptr);
  void doFor(SyntaxTreeNode* father = nullptr);

 private:
  // size_t index_;
  const std::list<Token*>& tokens_;
  std::list<Token*>::const_iterator cit_;
  SyntaxTree* tree_;
};
