#include "../include/parser.h"
#include "../include/error.h"

Parser::Parser(const std::list<Token*>& tokens)
    : index_(0), tokens_(tokens), cit_(tokens_.cbegin()), tree_(nullptr) {
  tree_ = new SyntaxTree();
}

Parser::~Parser() { delete tree_; }

SyntaxTree* Parser::getSyntaxTree() {
  tree_->setCurrent(new SyntaxTreeNode(TreeNodeValue::Sentence));
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

  if ((tokenType == TokenType::SHARP) &&
      ((*ncit)->getType() == TokenType::INCLUDE)) {
    return SentencePattern::INCLUDE;
  } else if (Token::isControlKeyWord(tokenValue)) {
    return SentencePattern::CONTROL;
  } else if (Token::isDataKeyWord(tokenValue) &&
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
    } else if ((*ncit)->getType() == TokenType::ASSIGN) {
      return SentencePattern::ASSIGNMENT;
    } else {
      return SentencePattern::ERROR;
    }
  } else if (tokenType == TokenType::RETURN) {
    return SentencePattern::RETURN;
  } else if (tokenType == TokenType::RB_BRACKET) {
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
  includeTree->setCurrent(new SyntaxTreeNode(TreeNodeValue::Include));
}

void Parser::doFunctionStatement() {}

void Parser::doStatement() {}

void Parser::doFunctionCall() {}