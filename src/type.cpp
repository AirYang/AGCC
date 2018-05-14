#include "../include/type.h"

const char* tokenTypeToStr(enum TokenType tk) {
#define TOKENTYPE_TO_STR(x) \
  case x:                   \
    return (#x);

  switch (tk) {
    TOKENTYPE_TO_STR(TokenType::KEY_WORD)
    TOKENTYPE_TO_STR(TokenType::IDENTIFIER)
    TOKENTYPE_TO_STR(TokenType::DIGIT_CONSTANT)
    TOKENTYPE_TO_STR(TokenType::OPERATOR)
    TOKENTYPE_TO_STR(TokenType::SEPARATOR)
    TOKENTYPE_TO_STR(TokenType::STRING_CONSTANT)
    TOKENTYPE_TO_STR(TokenType::INCLUDE)
    TOKENTYPE_TO_STR(TokenType::INT)
    TOKENTYPE_TO_STR(TokenType::FLOAT)
    TOKENTYPE_TO_STR(TokenType::CHAR)
    TOKENTYPE_TO_STR(TokenType::DOUBLE)
    TOKENTYPE_TO_STR(TokenType::FOR)
    TOKENTYPE_TO_STR(TokenType::IF)
    TOKENTYPE_TO_STR(TokenType::ELSE)
    TOKENTYPE_TO_STR(TokenType::WHILE)
    TOKENTYPE_TO_STR(TokenType::DO)
    TOKENTYPE_TO_STR(TokenType::RETURN)
    TOKENTYPE_TO_STR(TokenType::ASSIGN)
    TOKENTYPE_TO_STR(TokenType::ADDRESS)
    TOKENTYPE_TO_STR(TokenType::LT)
    TOKENTYPE_TO_STR(TokenType::GT)
    TOKENTYPE_TO_STR(TokenType::SELF_PLUS)
    TOKENTYPE_TO_STR(TokenType::SELF_MINUS)
    TOKENTYPE_TO_STR(TokenType::PLUS)
    TOKENTYPE_TO_STR(TokenType::MINUS)
    TOKENTYPE_TO_STR(TokenType::MUL)
    TOKENTYPE_TO_STR(TokenType::DIV)
    TOKENTYPE_TO_STR(TokenType::GET)
    TOKENTYPE_TO_STR(TokenType::LET)
    TOKENTYPE_TO_STR(TokenType::LL_BRACKET)
    TOKENTYPE_TO_STR(TokenType::RL_BRACKET)
    TOKENTYPE_TO_STR(TokenType::LB_BRACKET)
    TOKENTYPE_TO_STR(TokenType::RB_BRACKET)
    TOKENTYPE_TO_STR(TokenType::LM_BRACKET)
    TOKENTYPE_TO_STR(TokenType::RM_BRACKET)
    TOKENTYPE_TO_STR(TokenType::COMMA)
    TOKENTYPE_TO_STR(TokenType::DOUBLE_QUOTE)
    TOKENTYPE_TO_STR(TokenType::SEMICOLON)
    TOKENTYPE_TO_STR(TokenType::SHARP)
    // maybe add tree node type
    TOKENTYPE_TO_STR(TokenType::FIELD_TYPE)
  TOKENTYPE_TO_STR(TokenType::Constant)
  TOKENTYPE_TO_STR(TokenType::_Constant)
  TOKENTYPE_TO_STR(TokenType::Variable)
  TOKENTYPE_TO_STR(TokenType::_Variable)
  TOKENTYPE_TO_STR(TokenType::ArrayItem)
  TOKENTYPE_TO_STR(TokenType::_ArrayName)
  TOKENTYPE_TO_STR(TokenType::_ArrayIndex)
  TOKENTYPE_TO_STR(TokenType::Operator)
  TOKENTYPE_TO_STR(TokenType::_Operator)
  TOKENTYPE_TO_STR(TokenType::SingleOperand)
  TOKENTYPE_TO_STR(TokenType::DoubleOperand)
  TOKENTYPE_TO_STR(TokenType::FUNCTION_NAME)
  TOKENTYPE_TO_STR(TokenType::WhileControl)
  TOKENTYPE_TO_STR(TokenType::ForControl)
  TOKENTYPE_TO_STR(TokenType::IfElseControl)
    TOKENTYPE_TO_STR(TokenType::NOT_A_TYPE)
  }

#undef TOKENTYPE_TO_STR
  return "Unsupported Token Type";
}

// const char* treeNodeValueToStr(enum TreeNodeValue tnv) {
// #define TREENODEVALUE_TO_STR(x) \
//   case x:                       \
//     return (#x);

//   switch (tnv) {
//     TREENODEVALUE_TO_STR(TreeNodeValue::Sentence)
//     TREENODEVALUE_TO_STR(TreeNodeValue::Include)
//     TREENODEVALUE_TO_STR(TreeNodeValue::Statement)
//     TREENODEVALUE_TO_STR(TreeNodeValue::Assignment)
//     TREENODEVALUE_TO_STR(TreeNodeValue::Control)
//     TREENODEVALUE_TO_STR(TreeNodeValue::Expression)
//     TREENODEVALUE_TO_STR(TreeNodeValue::Constant)
//     TREENODEVALUE_TO_STR(TreeNodeValue::FunctionStatement)
//     TREENODEVALUE_TO_STR(TreeNodeValue::FunctionCall)
//     TREENODEVALUE_TO_STR(TreeNodeValue::NOT_A_VALUE)
//   }

// #undef TREENODEVALUE_TO_STR
//   return "Unsupported Tree Node Value";
// }

// const char* treeNodeTypeToStr(enum TreeNodeType tnt) {
// #define TREENODETYPE_TO_STR(x) \
//   case x:                      \
//     return (#x);

//   switch (tnt) {
//     TREENODETYPE_TO_STR(TreeNodeType::IDENTIFIER)
//     TREENODETYPE_TO_STR(TreeNodeType::FIELD_TYPE)
//     TREENODETYPE_TO_STR(TreeNodeType::DIGIT_CONSTANT)
//     TREENODETYPE_TO_STR(TreeNodeType::NOT_A_TYPE)
//     TREENODETYPE_TO_STR(TreeNodeType::Constant)
//     TREENODETYPE_TO_STR(TreeNodeType::_Constant)
//     TREENODETYPE_TO_STR(TreeNodeType::Variable)
//     TREENODETYPE_TO_STR(TreeNodeType::_Variable)
//     TREENODETYPE_TO_STR(TreeNodeType::ArrayItem)
//     TREENODETYPE_TO_STR(TreeNodeType::_ArrayName)
//     TREENODETYPE_TO_STR(TreeNodeType::_ArrayIndex)
//     TREENODETYPE_TO_STR(TreeNodeType::Operator)
//     TREENODETYPE_TO_STR(TreeNodeType::_Operator)
//     TREENODETYPE_TO_STR(TreeNodeType::LL_BRACKET)
//     TREENODETYPE_TO_STR(TreeNodeType::SingleOperand)
//     TREENODETYPE_TO_STR(TreeNodeType::DoubleOperand)
//     TREENODETYPE_TO_STR(TreeNodeType::FUNCTION_NAME)
//   }

// #undef TREENODETYPE_TO_STR
//   return "Unsupported Tree Node Type";
// }