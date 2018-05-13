#pragma once

#include <string>
#include <unordered_map>

#include "../include/type.h"

class SyntaxTreeNode {
 public:
  SyntaxTreeNode(const std::string& value = std::string(""),
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

 private:
  std::string value_;
  TokenType type_;
  std::unordered_map<std::string, std::string> extraInfo_;

  SyntaxTreeNode* father_;
  SyntaxTreeNode* left_;
  SyntaxTreeNode* right_;
  SyntaxTreeNode* firstSon_;
};

class SyntaxTree {};