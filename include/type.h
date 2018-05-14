#pragma once

enum class TokenType {
  // Token 分类(大类)
  KEY_WORD = 0,
  IDENTIFIER,
  DIGIT_CONSTANT,
  OPERATOR,
  SEPARATOR,
  STRING_CONSTANT,
  // Token 分类(小类)
  INCLUDE,
  INT,
  FLOAT,
  CHAR,
  DOUBLE,
  FOR,
  IF,
  ELSE,
  WHILE,
  DO,
  RETURN,
  ASSIGN,
  ADDRESS,
  LT,
  GT,
  SELF_PLUS,
  SELF_MINUS,
  PLUS,
  MINUS,
  MUL,
  DIV,
  GET,
  LET,
  LL_BRACKET,
  RL_BRACKET,
  LB_BRACKET,
  RB_BRACKET,
  LM_BRACKET,
  RM_BRACKET,
  COMMA,
  DOUBLE_QUOTE,
  SEMICOLON,
  SHARP,
  // FOR TREE NODE TYPE
  FIELD_TYPE,
  Constant,
  _Constant,
  Variable,
  _Variable,
  ArrayItem,
  _ArrayName,
  _ArrayIndex,
  Operator,
  _Operator,
  SingleOperand,
  DoubleOperand,
  FUNCTION_NAME,
  WhileControl,
  ForControl,
  IfElseControl,
  NOT_A_TYPE
};

enum class SentencePattern {
  INCLUDE = 0,
  CONTROL,
  FUNCTION_STATEMENT,
  STATEMENT,
  FUNCTION_CALL,
  ASSIGNMENT,
  RB_BRACKET,
  RETURN,
  ERROR
};

// enum class TreeNodeValue {
//   Sentence = 0,
//   Include,
//   Statement,
//   Assignment,
//   Control,
//   Expression,
//   Constant,
//   FunctionStatement,
//   FunctionCall,
//   NOT_A_VALUE
// };

// enum class TreeNodeType {
//   // IDENTIFIER = 0,
//   FIELD_TYPE,
//   // DIGIT_CONSTANT,
//   Constant,
//   _Constant,
//   Variable,
//   _Variable,
//   ArrayItem,
//   _ArrayName,
//   _ArrayIndex,
//   Operator,
//   _Operator,
//   // LL_BRACKET,
//   SingleOperand,
//   DoubleOperand,
//   FUNCTION_NAME,
//   NOT_A_TYPE
// };

const char* tokenTypeToStr(enum TokenType tk);
// const char* treeNodeValueToStr(enum TreeNodeValue tnv);
// const char* treeNodeTypeToStr(enum TreeNodeType tnt);