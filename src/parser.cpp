#include <stack>
#include <vector>

#include "../include/error.h"
#include "../include/parser.h"

Parser::Parser(const std::list<Token*>& tokens)
    : tokens_(tokens), cit_(tokens_.cbegin()), tree_(nullptr) {
  tree_ = new SyntaxTree(nullptr, nullptr, true);
}

Parser::~Parser() { delete tree_; }

SyntaxTree* Parser::getSyntaxTree() {
  tree_->setCurrent(new SyntaxTreeNode("Sentence"));
  tree_->setRoot(tree_->getCurrent());

  while (cit_ != tokens_.cend()) {
    switch (judgeSentencePattern()) {
      case SentencePattern::INCLUDE: {
        doInclude();
        break;
      }
      case SentencePattern::FUNCTION_STATEMENT: {
        doFunctionStatement();
        break;
      }
      case SentencePattern::STATEMENT: {
        doStatement();
        break;
      }
      case SentencePattern::FUNCTION_CALL: {
        doFunctionCall();
        break;
      }
      default: {
#ifdef DEBUG
        perror("Can't detect sentencePattern\n");
#endif  // DEBUG
        error(__FILE__, __FUNCTION__, __LINE__);
        break;
      }
    }
  }
  return tree_;
}

SentencePattern Parser::judgeSentencePattern() {
  std::string tokenValue = (*cit_)->getValue();
  TokenType tokenType = (*cit_)->getType();

  auto ncit = cit_;
  ++ncit;

  if ((tokenType == TokenType::SHARP) && (ncit != tokens_.cend()) &&
      ((*ncit)->getType() == TokenType::INCLUDE)) {
    return SentencePattern::INCLUDE;
  } else if (Token::isControlKeyWord(tokenValue)) {
    return SentencePattern::CONTROL;
  } else if (Token::isDataKeyWord(tokenValue) && (ncit != tokens_.cend()) &&
             ((*ncit)->getType() == TokenType::IDENTIFIER)) {
    auto nncit = ncit;
    ++nncit;

    if ((*nncit)->getType() == TokenType::LL_BRACKET) {
      return SentencePattern::FUNCTION_STATEMENT;
    } else if (((*nncit)->getType() == TokenType::SEMICOLON) ||
               ((*nncit)->getType() == TokenType::LM_BRACKET) ||
               ((*nncit)->getType() == TokenType::COMMA)) {
      return SentencePattern::STATEMENT;
    } else {
      return SentencePattern::ERROR;
    }
  } else if (tokenType == TokenType::IDENTIFIER) {
    if ((*ncit)->getType() == TokenType::LL_BRACKET) {
      return SentencePattern::FUNCTION_CALL;
    } else if ((ncit != tokens_.cend()) &&
               ((*ncit)->getType() == TokenType::ASSIGN)) {
      return SentencePattern::ASSIGNMENT;
    } else {
      return SentencePattern::ERROR;
    }
  } else if (tokenType == TokenType::RETURN) {
    return SentencePattern::RETURN;
  } else if (tokenType == TokenType::RB_BRACKET) {
    ++cit_;
    return SentencePattern::RB_BRACKET;
  } else {
    return SentencePattern::ERROR;
  }
}

void Parser::doInclude(SyntaxTreeNode* father) {
  if (father == nullptr) {
    father = tree_->getRoot();
  }
  SyntaxTree* includeTree = new SyntaxTree();
  includeTree->setCurrent(new SyntaxTreeNode("Include"));
  includeTree->setRoot(includeTree->getCurrent());
  tree_->addChild(includeTree->getRoot(), father);

  size_t cnt = 0;
  for (bool flag = true; flag;) {
    if ((*cit_)->getType() == TokenType::DOUBLE_QUOTE) {
      ++cnt;
    }

    if ((cit_ == tokens_.end()) || (cnt == 2) ||
        ((*cit_)->getType() == TokenType::GT)) {
      flag = false;
    }

    includeTree->addChild(new SyntaxTreeNode((*cit_)->getValue()),
                          includeTree->getRoot());
    ++cit_;
  }

  delete includeTree;
}

void Parser::doFunctionStatement(SyntaxTreeNode* father) {
  if (father == nullptr) {
    father = tree_->getRoot();
  }
  SyntaxTree* funcStatementTree = new SyntaxTree();
  funcStatementTree->setCurrent(new SyntaxTreeNode("FunctionStatement"));
  funcStatementTree->setRoot(funcStatementTree->getCurrent());
  tree_->addChild(funcStatementTree->getRoot(), father);

  for (bool flag = true; flag && (cit_ != tokens_.end());) {
    if (Token::isDataKeyWord((*cit_)->getValue())) {
      SyntaxTreeNode* returnType = new SyntaxTreeNode("Type");
      funcStatementTree->addChild(returnType);
      funcStatementTree->addChild(
          new SyntaxTreeNode((*cit_)->getValue(), TokenType::FIELD_TYPE,
                             {{"type", (*cit_)->getValue()}}));
      ++cit_;
    } else if ((*cit_)->getType() == TokenType::IDENTIFIER) {
      SyntaxTreeNode* funcName = new SyntaxTreeNode("FunctionName");
      funcStatementTree->addChild(funcName, funcStatementTree->getRoot());
      funcStatementTree->addChild(
          new SyntaxTreeNode((*cit_)->getValue(), TokenType::IDENTIFIER,
                             {{"type", "FunctionName"}}));
      ++cit_;
    } else if ((*cit_)->getType() == TokenType::LL_BRACKET) {
      SyntaxTreeNode* paramsList = new SyntaxTreeNode("StateParameterList");
      funcStatementTree->addChild(paramsList, funcStatementTree->getRoot());
      ++cit_;
      while ((*cit_)->getType() != TokenType::RL_BRACKET) {
        if (Token::isDataKeyWord((*cit_)->getValue())) {
          SyntaxTreeNode* param = new SyntaxTreeNode("Parameter");
          funcStatementTree->addChild(param, paramsList);
          funcStatementTree->addChild(
              new SyntaxTreeNode((*cit_)->getValue(), TokenType::FIELD_TYPE,
                                 {{"type", (*cit_)->getValue()}}),
              param);

          auto ncit = cit_;
          ++ncit;
          if ((*ncit)->getType() == TokenType::IDENTIFIER) {
            funcStatementTree->addChild(
                new SyntaxTreeNode((*ncit)->getValue(), TokenType::IDENTIFIER,
                                   {{"type", "VARIABLE"},
                                    {"variable_type", (*cit_)->getValue()}}),
                param);
          } else {
#ifdef DEBUG
            perror("error function param\n");
#endif  // DEBUG
            error(__FILE__, __FUNCTION__, __LINE__);
          }
          ++cit_;
        }
        ++cit_;
      }
      ++cit_;
    } else if ((*cit_)->getType() == TokenType::LB_BRACKET) {
      doBlock(funcStatementTree);
    }
  }

  delete funcStatementTree;
}

void Parser::doBlock(SyntaxTree* fatherTree) {
  ++cit_;
  SyntaxTree* sentenceTree = new SyntaxTree();
  sentenceTree->setCurrent(new SyntaxTreeNode("Sentence"));
  sentenceTree->setRoot(sentenceTree->getCurrent());
  fatherTree->addChild(sentenceTree->getRoot(), fatherTree->getRoot());
  while (true) {
    switch (judgeSentencePattern()) {
      case SentencePattern::STATEMENT: {
        doStatement(sentenceTree->getRoot());
        break;
      }
      case SentencePattern::ASSIGNMENT: {
        doAssignment(sentenceTree->getRoot());
        break;
      }
      case SentencePattern::FUNCTION_CALL: {
        doFunctionCall(sentenceTree->getRoot());
        break;
      }
      case SentencePattern::CONTROL: {
        doControl(sentenceTree->getRoot());
        break;
      }
      case SentencePattern::RETURN: {
        doReturn(sentenceTree->getRoot());
        break;
      }
      case SentencePattern::RB_BRACKET: {
        goto EXIT_BLOCK;
        break;
      }
      default: {
#ifdef DEBUG
        perror("block judge sentence pattern error\n");
#endif  // DEBUG
        error(__FILE__, __FUNCTION__, __LINE__);
        break;
      }
    }
  }
EXIT_BLOCK:
  delete sentenceTree;
}

void Parser::doStatement(SyntaxTreeNode* father) {
  if (father == nullptr) {
    father = tree_->getRoot();
  }
  SyntaxTree* statementTree = new SyntaxTree();
  statementTree->setCurrent(new SyntaxTreeNode("Statement"));
  statementTree->setRoot(statementTree->getCurrent());
  tree_->addChild(statementTree->getRoot(), father);

  std::string tmpVariableType;
  while ((*cit_)->getType() != TokenType::SEMICOLON) {
    if (Token::isDataKeyWord((*cit_)->getValue())) {
      tmpVariableType = (*cit_)->getValue();
      SyntaxTreeNode* variableType = new SyntaxTreeNode("Type");
      statementTree->addChild(variableType);
      statementTree->addChild(
          new SyntaxTreeNode((*cit_)->getValue(), TokenType::FIELD_TYPE,
                             {{"type", (*cit_)->getValue()}}));
    } else if ((*cit_)->getType() == TokenType::IDENTIFIER) {
      statementTree->addChild(
          new SyntaxTreeNode(
              (*cit_)->getValue(), TokenType::IDENTIFIER,
              {{"type", "VARIABLE"}, {"variable_type", tmpVariableType}}),
          statementTree->getRoot());
    } else if ((*cit_)->getType() == TokenType::DIGIT_CONSTANT) {
      statementTree->addChild(
          new SyntaxTreeNode((*cit_)->getValue(), TokenType::DIGIT_CONSTANT),
          statementTree->getRoot());
      statementTree->getCurrent()->getLeft()->setExtraInfo(
          {{"type", "LIST"}, {"list_type", tmpVariableType}});
    } else if ((*cit_)->getType() == TokenType::LB_BRACKET) {
      ++cit_;
      SyntaxTreeNode* constantList = new SyntaxTreeNode("ConstantList");
      statementTree->addChild(constantList, statementTree->getRoot());
      while ((*cit_)->getType() != TokenType::RB_BRACKET) {
        if ((*cit_)->getType() == TokenType::DIGIT_CONSTANT) {
          statementTree->addChild(new SyntaxTreeNode((*cit_)->getValue(),
                                                     TokenType::DIGIT_CONSTANT),
                                  constantList);
        }
        ++cit_;
      }
    } else if ((*cit_)->getType() == TokenType::COMMA) {
      while ((*cit_)->getType() != TokenType::SEMICOLON) {
        if ((*cit_)->getType() == TokenType::IDENTIFIER) {
          SyntaxTree* tree = new SyntaxTree();
          tree->setCurrent(new SyntaxTreeNode("Statement"));
          tree->setRoot(tree->getCurrent());
          tree_->addChild(tree->getRoot(), father);

          SyntaxTreeNode* variableType = new SyntaxTreeNode("Type");
          tree->addChild(variableType);

          tree->addChild(new SyntaxTreeNode(tmpVariableType,
                                            TokenType::FIELD_TYPE,
                                            {{"type", tmpVariableType}}));
          tree->addChild(
              new SyntaxTreeNode(
                  (*cit_)->getValue(), TokenType::IDENTIFIER,
                  {{"type", "VARIABLE"}, {"variable_type", tmpVariableType}}),
              tree->getRoot());

          delete tree;
        }
        ++cit_;
      }
      break;
    }
    ++cit_;
  }
  ++cit_;
  delete statementTree;
}

void Parser::doAssignment(SyntaxTreeNode* father) {
  if (father == nullptr) {
    father = tree_->getRoot();
  }
  SyntaxTree* assignTree = new SyntaxTree();
  assignTree->setCurrent(new SyntaxTreeNode("Assignment"));
  assignTree->setRoot(assignTree->getCurrent());
  tree_->addChild(assignTree->getRoot(), father);
  while ((*cit_)->getType() != TokenType::SEMICOLON) {
    if ((*cit_)->getType() == TokenType::IDENTIFIER) {
      assignTree->addChild(
          new SyntaxTreeNode((*cit_)->getValue(), TokenType::IDENTIFIER));
      ++cit_;
    } else if ((*cit_)->getType() == TokenType::ASSIGN) {
      ++cit_;
      doExpression(tokens_.cend(), assignTree->getRoot());
    }
  }
  ++cit_;
  delete assignTree;
}

// may some prob
void Parser::doExpression(std::list<Token*>::const_iterator citEnd,
                          SyntaxTreeNode* father) {
  if (father == nullptr) {
    father = tree_->getRoot();
  }
  std::unordered_map<std::string, size_t> operatorPriorityMap = {
      {">", 0}, {"<", 0}, {">=", 0}, {"<=", 0}, {"+", 1}, {"-", 1},
      {"*", 2}, {"/", 2}, {"++", 3}, {"--", 3}, {"!", 3}};

  std::stack<SyntaxTree*> operatorTreeStack;
  // std::stack<SyntaxTreeNode*> operatorNodeStack;
  std::vector<SyntaxTree*> reversePolichExpression;
  while ((*cit_)->getType() != TokenType::SEMICOLON) {
    if (cit_ == citEnd) {
      break;
    }
    if ((*cit_)->getType() == TokenType::DIGIT_CONSTANT) {
      SyntaxTree* tree = new SyntaxTree();
      tree->setCurrent(new SyntaxTreeNode("Expression", TokenType::Constant));
      tree->setRoot(tree->getCurrent());
      tree->addChild(
          new SyntaxTreeNode((*cit_)->getValue(), TokenType::_Constant));
      reversePolichExpression.push_back(tree);
    } else if ((*cit_)->getType() == TokenType::IDENTIFIER) {
      auto ncit = cit_;
      ++ncit;
      if ((Token::isOperator((*ncit)->getValue())) ||
          ((*ncit)->getType() == TokenType::SEMICOLON)) {
        SyntaxTree* tree = new SyntaxTree();
        tree->setCurrent(new SyntaxTreeNode("Expression", TokenType::Variable));
        tree->setRoot(tree->getCurrent());
        tree->addChild(
            new SyntaxTreeNode((*cit_)->getValue(), TokenType::_Variable));
        reversePolichExpression.push_back(tree);
      } else if ((*ncit)->getType() == TokenType::LM_BRACKET) {
        SyntaxTree* tree = new SyntaxTree();
        tree->setCurrent(
            new SyntaxTreeNode("Expression", TokenType::ArrayItem));
        tree->setRoot(tree->getCurrent());
        tree->addChild(
            new SyntaxTreeNode((*cit_)->getValue(), TokenType::_ArrayName));
        ++cit_;
        ++cit_;
        if (((*cit_)->getType() != TokenType::DIGIT_CONSTANT) &&
            ((*cit_)->getType() != TokenType::IDENTIFIER)) {
#ifdef DEBUG
          perror("array index must be DIGIT_CONSTANT or IDENTIFIER: ");
          perror(tokenTypeToStr((*cit_)->getType()));
          perror("\n");
#endif  // DEBUG
          error(__FILE__, __FUNCTION__, __LINE__);
        } else {
          tree->addChild(
              new SyntaxTreeNode((*cit_)->getValue(), TokenType::_ArrayIndex),
              tree->getRoot());
          reversePolichExpression.push_back(tree);
        }
      }
    } else if ((Token::isOperator((*cit_)->getValue())) ||
               ((*cit_)->getType() == TokenType::LL_BRACKET) ||
               ((*cit_)->getType() == TokenType::RL_BRACKET)) {
      SyntaxTree* tree = new SyntaxTree();
      tree->setCurrent(new SyntaxTreeNode("Operator", TokenType::Operator));
      tree->setRoot(tree->getCurrent());
      tree->addChild(
          new SyntaxTreeNode((*cit_)->getValue(), TokenType::_Operator));
      if ((*cit_)->getType() == TokenType::LL_BRACKET) {
        // may be use
        tree->getCurrent()->setType(TokenType::LL_BRACKET);
        tree->setControlFlag(true);
        operatorTreeStack.push(tree);
      } else if ((*cit_)->getType() == TokenType::RL_BRACKET) {
        // should be debug
        while ((!operatorTreeStack.empty()) &&
               (operatorTreeStack.top()->getCurrent()->getType() !=
                TokenType::LL_BRACKET)) {
          reversePolichExpression.push_back(operatorTreeStack.top());
          operatorTreeStack.pop();
        }
        if (!operatorTreeStack.empty()) {
          // may be free
          SyntaxTree* befreeTree = operatorTreeStack.top();
          operatorTreeStack.pop();
          delete befreeTree;
        }
        // may be free
        // delete tree;
      } else {
        while ((!operatorTreeStack.empty()) &&
               (operatorPriorityMap.at(tree->getCurrent()->getValue()) <
                operatorPriorityMap.at(
                    operatorTreeStack.top()->getCurrent()->getValue()))) {
          reversePolichExpression.push_back(operatorTreeStack.top());
          operatorTreeStack.pop();
        }
        operatorTreeStack.push(tree);
      }
    }
    ++cit_;
  }

  while (!operatorTreeStack.empty()) {
    reversePolichExpression.push_back(operatorTreeStack.top());
    operatorTreeStack.pop();
  }

  std::vector<SyntaxTree*> operandStack;
  std::unordered_set<std::string> unaryOperators{"!", "++", "--"};
  std::unordered_set<std::string> binaryOperators{"+", "-", "*",  "/",
                                                  ">", "<", ">=", "<="};

  for (auto item : reversePolichExpression) {
    if (item->getRoot()->getType() != TokenType::Operator) {
      operandStack.push_back(item);
    } else {
      if (unaryOperators.find(item->getCurrent()->getValue()) !=
          unaryOperators.end()) {
        auto aTree = operandStack.at(operandStack.size() - 1);
        operandStack.pop_back();
        SyntaxTree* newTree = new SyntaxTree();
        newTree->setCurrent(
            new SyntaxTreeNode("Expression", TokenType::SingleOperand));
        newTree->setRoot(newTree->getCurrent());
        newTree->addChild(item->getRoot());
        newTree->addChild(aTree->getRoot(), newTree->getRoot());
        operandStack.push_back(newTree);
        // delete aTree;
      } else if (binaryOperators.find(item->getCurrent()->getValue()) !=
                 binaryOperators.end()) {
        auto bTree = operandStack.at(operandStack.size() - 1);
        operandStack.pop_back();
        auto aTree = operandStack.at(operandStack.size() - 1);
        operandStack.pop_back();
        auto newTree = new SyntaxTree();
        newTree->setCurrent(
            new SyntaxTreeNode("Expression", TokenType::DoubleOperand));
        newTree->setRoot(newTree->getCurrent());
        newTree->addChild(aTree->getRoot());
        newTree->addChild(item->getRoot(), newTree->getRoot());
        newTree->addChild(bTree->getRoot(), newTree->getRoot());
        operandStack.push_back(newTree);
        // delete aTree;
        // delete bTree;
      } else {
#ifdef DEBUG
        perror("operator not supported: ");
        perror((item->getCurrent()->getValue()).c_str());
        perror("\n");
#endif  // DEBUG
        error(__FILE__, __FUNCTION__, __LINE__);
      }
    }
  }
  tree_->addChild(operandStack.at(0)->getRoot(), father);
  for (auto& befreeTree : operandStack) {
    delete befreeTree;
    for (auto& befreeTree2 : reversePolichExpression) {
      if (befreeTree2 == befreeTree) {
        befreeTree2 = nullptr;
      }
    }
    befreeTree = nullptr;
  }

  for (auto& befreeTree : reversePolichExpression) {
    delete befreeTree;
  }
}

void Parser::doFunctionCall(SyntaxTreeNode* father) {
  if (father == nullptr) {
    father = tree_->getRoot();
  }

  auto funcCallTree = new SyntaxTree();
  funcCallTree->setCurrent(new SyntaxTreeNode("FunctionCall"));
  funcCallTree->setRoot(funcCallTree->getCurrent());
  tree_->addChild(funcCallTree->getRoot(), father);
  while ((*cit_)->getType() != TokenType::SEMICOLON) {
    if ((*cit_)->getType() == TokenType::IDENTIFIER) {
      funcCallTree->addChild(
          new SyntaxTreeNode((*cit_)->getValue(), TokenType::FUNCTION_NAME));
    } else if ((*cit_)->getType() == TokenType::LL_BRACKET) {
      ++cit_;
      auto paramsList = new SyntaxTreeNode("CallParameterList");
      funcCallTree->addChild(paramsList, funcCallTree->getRoot());
      while ((*cit_)->getType() != TokenType::RL_BRACKET) {
        if (((*cit_)->getType() == TokenType::IDENTIFIER) ||
            ((*cit_)->getType() == TokenType::DIGIT_CONSTANT) ||
            ((*cit_)->getType() == TokenType::STRING_CONSTANT)) {
          funcCallTree->addChild(
              new SyntaxTreeNode((*cit_)->getValue(), (*cit_)->getType()),
              paramsList);
        } else if ((*cit_)->getType() == TokenType::DOUBLE_QUOTE) {
          ++cit_;
          funcCallTree->addChild(
              new SyntaxTreeNode((*cit_)->getValue(), (*cit_)->getType()),
              paramsList);
          ++cit_;
        } else if ((*cit_)->getType() == TokenType::ADDRESS) {
          funcCallTree->addChild(
              new SyntaxTreeNode((*cit_)->getValue(), (*cit_)->getType()),
              paramsList);
        }
        ++cit_;
      }
    } else {
#ifdef DEBUG
      perror("function call error!\n");
#endif  // DEBUG
      error(__FILE__, __FUNCTION__, __LINE__);
    }
    ++cit_;
  }
  ++cit_;
  delete funcCallTree;
}

void Parser::doControl(SyntaxTreeNode* father) {
  TokenType tt = (*cit_)->getType();
  if ((tt == TokenType::WHILE) || (tt == TokenType::DO)) {
    doWhile(father);
  } else if (tt == TokenType::IF) {
    doIfElse(father);
  } else if (tt == TokenType::FOR) {
    doFor(father);
  } else {
#ifdef DEBUG
    perror("control style not supported!\n");
#endif  // DEBUG
    error(__FILE__, __FUNCTION__, __LINE__);
  }
}

void Parser::doWhile(SyntaxTreeNode* father) {
  auto whileTree = new SyntaxTree();
  whileTree->setCurrent(new SyntaxTreeNode("Control", TokenType::WhileControl));
  whileTree->setRoot(whileTree->getCurrent());
  tree_->addChild(whileTree->getRoot(), father);
  ++cit_;
  if ((*cit_)->getType() == TokenType::LL_BRACKET) {
    auto ncit = cit_;
    while ((*ncit)->getType() != TokenType::RL_BRACKET) {
      ++ncit;
    }
    doExpression(ncit, whileTree->getRoot());
    if ((*cit_)->getType() == TokenType::LB_BRACKET) {
      doBlock(whileTree);
    }
  }
  delete whileTree;
}

void Parser::doIfElse(SyntaxTreeNode* father) {
  auto ifElseTree = new SyntaxTree();
  ifElseTree->setCurrent(
      new SyntaxTreeNode("Control", TokenType::IfElseControl));
  ifElseTree->setRoot(ifElseTree->getCurrent());
  tree_->addChild(ifElseTree->getRoot(), father);

  auto ifTree = new SyntaxTree();
  ifTree->setCurrent(new SyntaxTreeNode("IfControl"));
  ifTree->setRoot(ifTree->getCurrent());
  ifElseTree->addChild(ifTree->getRoot());

  if ((*cit_)->getType() == TokenType::IF) {
    ++cit_;
    if ((*cit_)->getType() == TokenType::LL_BRACKET) {
      ++cit_;
      auto ncit = cit_;
      while ((*ncit)->getType() != TokenType::RL_BRACKET) {
        ++ncit;
      }
      doExpression(ncit, ifTree->getRoot());
      ++cit_;
    } else {
#ifdef DEBUG
      perror("lack of left bracket!\n");
#endif  // DEBUG
      error(__FILE__, __FUNCTION__, __LINE__);
    }

    if ((*cit_)->getType() == TokenType::LB_BRACKET) {
      doBlock(ifTree);
    }
  }

  if ((*cit_)->getType() == TokenType::ELSE) {
    ++cit_;
    auto elseTree = new SyntaxTree();
    elseTree->setCurrent(new SyntaxTreeNode("ElseControl"));
    elseTree->setRoot(elseTree->getCurrent());
    ifElseTree->addChild(elseTree->getRoot(), ifElseTree->getRoot());
    if ((*cit_)->getType() == TokenType::LB_BRACKET) {
      doBlock(elseTree);
    }
    delete elseTree;
  }

  delete ifTree;
  delete ifElseTree;
}

void Parser::doFor(SyntaxTreeNode* father) {
  auto forTree = new SyntaxTree();
  forTree->setCurrent(new SyntaxTreeNode("Control", TokenType::ForControl));
  forTree->setRoot(forTree->getCurrent());
  tree_->addChild(forTree->getRoot(), father);

  while (true) {
    auto tt = (*cit_)->getType();
    if (tt == TokenType::FOR) {
      ++cit_;
    } else if (tt == TokenType::LL_BRACKET) {
      ++cit_;
      auto ncit = cit_;
      while ((*ncit)->getType() != TokenType::RL_BRACKET) {
        ++ncit;
      }
      doAssignment(forTree->getRoot());
      doExpression(tokens_.cend(), forTree->getRoot());
      ++cit_;
      doExpression(ncit, forTree->getRoot());
      ++cit_;
    } else if (tt == TokenType::LB_BRACKET) {
      doBlock(forTree);
      break;
    }
  }
  auto currentNode = forTree->getRoot()->getFirstSon()->getRight()->getRight();
  auto nextNode = currentNode->getRight();
  forTree->swapBrotherNode(currentNode, nextNode);

  delete forTree;
}

void Parser::doReturn(SyntaxTreeNode* father) {
  if (father == nullptr) {
    father = tree_->getRoot();
  }

  auto returnTree = new SyntaxTree();
  returnTree->setCurrent(new SyntaxTreeNode("Return"));
  returnTree->setRoot(returnTree->getCurrent());
  tree_->addChild(returnTree->getRoot(), father);

  while ((*cit_)->getType() != TokenType::SEMICOLON) {
    if ((*cit_)->getType() == TokenType::RETURN) {
      returnTree->addChild(new SyntaxTreeNode((*cit_)->getValue()));
      ++cit_;
    } else {
      doExpression(tokens_.cend(), returnTree->getRoot());
    }
  }
  ++cit_;
  delete returnTree;
}