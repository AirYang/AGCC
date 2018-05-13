#include <cassert>

#include "../include/syntax_tree.h"

SyntaxTreeNode::SyntaxTreeNode(
    TreeNodeValue value, TreeNodeType type,
    const std::unordered_map<std::string, std::string>& extraInfo)
    : value_(value),
      type_(type),
      extraInfo_(extraInfo),
      father_(nullptr),
      left_(nullptr),
      right_(nullptr),
      firstSon_(nullptr) {}

SyntaxTreeNode::~SyntaxTreeNode() {}

TreeNodeValue SyntaxTreeNode::getValue() const { return value_; }

TreeNodeType SyntaxTreeNode::getType() const { return type_; }

std::unordered_map<std::string, std::string> SyntaxTreeNode::getExtraInfo()
    const {
  return extraInfo_;
}

void SyntaxTreeNode::setValue(TreeNodeValue value) { value_ = value; }

void SyntaxTreeNode::setType(TreeNodeType type) { type_ = type; }

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

std::string SyntaxTreeNode::toString() const {
  std::string str = "";

  str += std::string("value[") + treeNodeValueToStr(value_) + "] type[" +
         treeNodeTypeToStr(type_) + "]";

  str +=
      std::string(" father[") +
      ((father_ != nullptr) ? treeNodeValueToStr(father_->value_) : "nullptr") +
      "]";

  str += std::string(" left[") +
         ((left_ != nullptr) ? treeNodeValueToStr(left_->value_) : "nullptr") +
         "]";

  str +=
      std::string(" right[") +
      ((right_ != nullptr) ? treeNodeValueToStr(right_->value_) : "nullptr") +
      "]";

  return str;
}

SyntaxTree::SyntaxTree(SyntaxTreeNode* root = nullptr,
                       SyntaxTreeNode* current = nullptr)
    : root_(root), current_(current) {}

SyntaxTree::~SyntaxTree() { freeNode(root_); }

SyntaxTreeNode* SyntaxTree::getRoot() const { return root_; }

SyntaxTreeNode* SyntaxTree::getCurrent() const { return current_; }

void SyntaxTree::setRoot(SyntaxTreeNode* root) { root_ = root; }

void SyntaxTree::setCurrent(SyntaxTreeNode* current) { current_ = current; }

void SyntaxTree::addChild(SyntaxTreeNode* child, SyntaxTreeNode* father) {
  if (father == nullptr) {
    father = current_;
  }
  child->setFather(father);
  if (father->getFirstSon() == nullptr) {
    father->setFirstSon(child);
  } else {
    current_ = father->getFirstSon();
    while (current_->getRight() != nullptr) {
      current_ = current_->getRight();
    }
    current_->setRight(child);
    child->setLeft(current_);
  }
  current_ = child;
}

void SyntaxTree::swapBrotherNode(SyntaxTreeNode* left, SyntaxTreeNode* right) {
  assert((left != nullptr) && (right != nullptr));
  assert((left->getRight() == right) && (right->getLeft() == left));

  SyntaxTreeNode* leftLeft = left->getLeft();
  SyntaxTreeNode* rightRight = right->getRight();

  left->setLeft(right);
  left->setRight(rightRight);
  right->setLeft(leftLeft);
  right->setRight(left);

  if (leftLeft != nullptr) {
    leftLeft->setRight(right);
  }

  if (rightRight != nullptr) {
    rightRight->setLeft(left);
  }
}

std::string SyntaxTree::toString() const {
  std::string str = "";
  str = toStringDo(root_);
  return str;
}

void SyntaxTree::freeNode(SyntaxTreeNode* node) {
  if (node == nullptr) {
    return;
  }
  freeNode(node->getRight());
  freeNode(node->getFirstSon());
  delete node;
}

std::string SyntaxTree::toStringDo(SyntaxTreeNode* node) const {
  if (node == nullptr) {
    return;
  }
  std::string str = std::string("  ") + node->toString() + "\n";
  SyntaxTreeNode* child = node->getFirstSon();
  while (child != nullptr) {
    str += toStringDo(child);
    child = child->getRight();
  }
  return str;
}