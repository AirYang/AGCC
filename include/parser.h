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
  void doFunctionStatement();
  void doStatement();
  void doFunctionCall();

 private:
  size_t index_;
  const std::list<Token*>& tokens_;
  std::list<Token*>::const_iterator cit_;
  SyntaxTree* tree_;
};
