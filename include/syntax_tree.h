#pragma once

#include <string>
#include <unordered_map>

#include "../include/type.h"

class SyntaxTreeNode {
 public:
  SyntaxTreeNode(const std::string& value = std::string(),
                 TokenType type = TokenType::NOT_A_TYPE,
                 const std::unordered_map<std::string, std::string>& extraInfo =
                     std::unordered_map<std::string, std::string>());
  ~SyntaxTreeNode();

 public:
  std::string getValue() const;
  TokenType getType() const;
  std::unordered_map<std::string, std::string> getExtraInfo() const;

  void setValue(const std::string& value);
  void setType(TokenType type);
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
  std::string value_;
  TokenType type_;
  std::unordered_map<std::string, std::string> extraInfo_;

  SyntaxTreeNode* father_;
  SyntaxTreeNode* left_;
  SyntaxTreeNode* right_;
  SyntaxTreeNode* firstSon_;
};

class SyntaxTree {
 public:
  SyntaxTree(SyntaxTreeNode* root = nullptr, SyntaxTreeNode* current = nullptr,
             bool controlFlag = false);
  ~SyntaxTree();

 public:
  SyntaxTreeNode* getRoot() const;
  SyntaxTreeNode* getCurrent() const;
  bool getControlFlag() const;
  void setRoot(SyntaxTreeNode* root);
  void setCurrent(SyntaxTreeNode* current);
  void setControlFlag(bool controlFlag);
  void addChild(SyntaxTreeNode* child, SyntaxTreeNode* father = nullptr);
  void swapBrotherNode(SyntaxTreeNode* left, SyntaxTreeNode* right);

  std::string toString() const;

 private:
  void freeNode(SyntaxTreeNode* node);
  std::string toStringDo(SyntaxTreeNode* node) const;

 private:
  SyntaxTreeNode* root_;
  SyntaxTreeNode* current_;
  bool controlFlag_;
};