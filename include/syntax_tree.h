#pragma once

#include <string>
#include <unordered_map>

#include "../include/type.h"

class SyntaxTreeNode {
 public:
  SyntaxTreeNode(TreeNodeValue value = TreeNodeValue::NOT_A_VALUE,
                 TreeNodeType type = TreeNodeType::NOT_A_TYPE,
                 const std::unordered_map<std::string, std::string>& extraInfo =
                     std::unordered_map<std::string, std::string>());
  ~SyntaxTreeNode();

 public:
  TreeNodeValue getValue() const;
  TreeNodeType getType() const;
  std::unordered_map<std::string, std::string> getExtraInfo() const;

  void setValue(TreeNodeValue value);
  void setType(TreeNodeType type);
  void setExtraInfo(
      const std::unordered_map<std::string, std::string>& extraInfo);

  SyntaxTreeNode* getFather() const;
  SyntaxTreeNode* getLeft() const;
  SyntaxTreeNode* getRight() const;
  SyntaxTreeNode* getFirstSon() const;

  void setFather(SyntaxTreeNode* father);
  void setLeft(SyntaxTreeNode* left);
  void setRight(SyntaxTreeNode* right);
  void setFirstSon(SyntaxTreeNode* firstSon);

  std::string toString() const;

 private:
  TreeNodeValue value_;
  TreeNodeType type_;
  std::unordered_map<std::string, std::string> extraInfo_;

  SyntaxTreeNode* father_;
  SyntaxTreeNode* left_;
  SyntaxTreeNode* right_;
  SyntaxTreeNode* firstSon_;
};

class SyntaxTree {
 public:
  SyntaxTree(SyntaxTreeNode* root = nullptr, SyntaxTreeNode* current = nullptr);
  ~SyntaxTree();

 public:
  SyntaxTreeNode* getRoot() const;
  SyntaxTreeNode* getCurrent() const;
  void setRoot(SyntaxTreeNode* root);
  void setCurrent(SyntaxTreeNode* current);
  void addChild(SyntaxTreeNode* child, SyntaxTreeNode* father = nullptr);
  void swapBrotherNode(SyntaxTreeNode* left, SyntaxTreeNode* right);

  std::string toString() const;

 private:
  void freeNode(SyntaxTreeNode* node);
  std::string toStringDo(SyntaxTreeNode* node) const;

 private:
  SyntaxTreeNode* root_;
  SyntaxTreeNode* current_;
};