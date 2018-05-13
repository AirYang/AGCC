#include "../include/syntax.h"

SyntaxTreeNode::SyntaxTreeNode(
    const std::string& value, TokenType type,
    const std::unordered_map<std::string, std::string>& extraInfo)
    : value_(value),
      type_(type),
      extraInfo_(extraInfo),
      father_(nullptr),
      left_(nullptr),
      right_(nullptr),
      firstSon_(nullptr) {}

SyntaxTreeNode::~SyntaxTreeNode() {}

std::string SyntaxTreeNode::getValue() const { return value_; }

TokenType SyntaxTreeNode::getType() const { return type_; }

std::unordered_map<std::string, std::string> SyntaxTreeNode::getExtraInfo()
    const {
  return extraInfo_;
}

void SyntaxTreeNode::setValue(const std::string& value) { value_ = value; }

void SyntaxTreeNode::setType(TokenType type) { type_ = type; }

void SyntaxTreeNode::setExtraInfo(
    const std::unordered_map<std::string, std::string>& extraInfo) {
  extraInfo_ = extraInfo;
}

SyntaxTreeNode* SyntaxTreeNode::getFather() const { return father_; }

SyntaxTreeNode* SyntaxTreeNode::getLeft() const { return left_; }

SyntaxTreeNode* SyntaxTreeNode::getRight() const { return right_; }

SyntaxTreeNode* SyntaxTreeNode::getFirstSon() const { return firstSon_; }

void SyntaxTreeNode::setFather(SyntaxTreeNode* father) { father_ = father; }

void SyntaxTreeNode::setLeft(SyntaxTreeNode* left) { left_ = left; }

void SyntaxTreeNode::setRight(SyntaxTreeNode* right) { right_ = right; }

void SyntaxTreeNode::setFirstSon(SyntaxTreeNode* firstSon) {
  firstSon_ = firstSon;
}
