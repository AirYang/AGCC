#include "../include/assembler.h"

#include <cassert>

#include <algorithm>
#include <fstream>

#include "../include/error.h"

AssemblerFileHandler::AssemblerFileHandler()
    : dataIndex_(1),
      bssIndex_(3),
      textIndex_(4),
      buffer_({".data", ".bss", ".lcomm bss_tmp, 4", ".text"}) {}

void AssemblerFileHandler::insert(const std::string& value, SegmentType type) {
  switch (type) {
    case SegmentType::DATA: {
      buffer_.insert(buffer_.begin() + dataIndex_, value);
      ++dataIndex_;
      ++bssIndex_;
      ++textIndex_;
      break;
    }
    case SegmentType::BSS: {
      buffer_.insert(buffer_.begin() + bssIndex_, value);
      ++bssIndex_;
      ++textIndex_;
      break;
    }
    case SegmentType::TEXT: {
      buffer_.insert(buffer_.begin() + textIndex_, value);
      ++textIndex_;
      break;
    }
    default: {
#ifdef DEBUG
      perror("AssemblerFileHandler can't insert this SegmentType\n");
#endif  // DEBUG
      error(__FILE__, __FUNCTION__, __LINE__);
      break;
    }
  }
}

bool AssemblerFileHandler::saveToFile(const std::string& fileName) {
  std::ofstream ofs(fileName);
  if (!ofs.is_open()) {
    return false;
  }
  std::for_each(buffer_.begin(), buffer_.end(),
                [&ofs](const std::string& elem) { ofs << elem << std::endl; });
  ofs.close();
  return true;
}

const std::unordered_set<std::string> Assembler::sentenceType_{
    "Sentence",   "Include", "FunctionStatement", "Statement", "FunctionCall",
    "Assignment", "Control", "Expression",        "Return"};

Assembler::Assembler(const SyntaxTree* tree)
    : labelCount_(0),
      tree_(tree),
      assFileHandler_(),
      operatorStack_(),
      operandStack_(),
      labelsIfElse_(),
      symbolTable_() {
  assert(tree_ != nullptr);
}

bool Assembler::saveToFile(const std::string& fileName) {
  traverse(tree_->getRoot());
  return assFileHandler_.saveToFile(fileName);
}

void Assembler::traverse(const SyntaxTreeNode* node) {
  auto nextNode = node;
  while (nextNode != nullptr) {
    handlerBlock(nextNode);
    nextNode = nextNode->getRight();
  }
}

void Assembler::handlerBlock(const SyntaxTreeNode* node) {
  if (node == nullptr) {
    return;
  }
  if (sentenceType_.find(node->getValue()) != sentenceType_.end()) {
    auto nodeValue = node->getValue();
    auto nodeType = node->getType();
    if (!nodeValue.compare("Sentence")) {
      traverse(node->getFirstSon());
    } else if (!nodeValue.compare("Include")) {
      doInclude(node);
    } else if (!nodeValue.compare("FunctionStatement")) {
      doFunctionStatement(node);
    } else if (!nodeValue.compare("Statement")) {
      doStatement(node);
    } else if (!nodeValue.compare("FunctionCall")) {
      doFunctionCall(node);
    } else if (!nodeValue.compare("Assignment")) {
      doAssignment(node);
    } else if (!nodeValue.compare("Control")) {
      switch (nodeType) {
        case TokenType::IfElseControl: {
          doControlIf(node);
          break;
        }
        case TokenType::ForControl: {
          doControlFor(node);
          break;
        }
        case TokenType::WhileControl: {
          doControlWhile(node);
          break;
        }
        default: {
#ifdef DEBUG
          perror("control type not support!\n");
#endif  // DEBUG
          error(__FILE__, __FUNCTION__, __LINE__);
          break;
        }
      }
    } else if (!nodeValue.compare("Expression")) {
      doExpression(node);
    } else if (!nodeValue.compare("Return")) {
      doReturn(node);
    } else {
#ifdef DEBUG
      perror("sentence type not supported yet!\n");
#endif  // DEBUG
      error(__FILE__, __FUNCTION__, __LINE__);
    }
  }
}

void Assembler::doInclude(const SyntaxTreeNode* node) { return; }

void Assembler::doFunctionStatement(const SyntaxTreeNode* node) {
  if (node == nullptr) {
    return;
  }
  auto nextNode = node->getFirstSon();
  while (nextNode != nullptr) {
    if (!(nextNode->getValue().compare("FunctionName"))) {
      if (nextNode->getFirstSon()->getValue().compare("main")) {
#ifdef DEBUG
        perror("only support main function\n");
#endif  // DEBUG
        error(__FILE__, __FUNCTION__, __LINE__);
      } else {
        assFileHandler_.insert(".globl main", SegmentType::TEXT);
        assFileHandler_.insert("main:", SegmentType::TEXT);
        assFileHandler_.insert("finit", SegmentType::TEXT);
      }
    } else if (!(nextNode->getValue().compare("Sentence"))) {
      traverse(nextNode->getFirstSon());
    }
    nextNode = nextNode->getRight();
  }
}

void Assembler::doStatement(const SyntaxTreeNode* node = nullptr) {
  if (node == nullptr) {
    return;
  }
  std::string line;
  bool initFlag = false;
  std::string variableName;
  std::string variableType;
  std::string variableFieldType;
  auto nextNode = node->getFirstSon();
  while (nextNode != nullptr) {
    if (!(nextNode->getValue().compare("Type"))) {
      variableFieldType = nextNode->getFirstSon()->getValue();
    } else if (nextNode->getType() == TokenType::IDENTIFIER) {
      variableName = nextNode->getValue();
      variableType = nextNode->getExtraInfo().at("type");
      line = std::string(".lcomm ") + variableName + ", " +
             doSizeof(variableFieldType);
    } else if (!(nextNode->getValue().compare("ConstantList"))) {
      line = variableName + ": ." + variableFieldType + " ";
      auto tmpNode = nextNode->getFirstSon();
      std::vector<std::string> array;
      while (tmpNode != nullptr) {
        array.push_back(tmpNode->getValue());
        tmpNode = tmpNode->getRight();
      }
      for (size_t i = 0; i < array.size(); i++) {
        line += array[i];
        if (i == (array.size() - 1)) continue;
        line += ", ";
      }
    }
    nextNode = nextNode->getRight();
  }
  assFileHandler_.insert(line, (!variableType.compare("VARIABLE"))
                                   ? (SegmentType::BSS)
                                   : (SegmentType::DATA));
  symbolTable_[variableName] = {{"type", variableType},
                                {"field_type", variableFieldType}};
}

std::string Assembler::doSizeof(const std::string type) {
  size_t length = 0;

  if ((!type.compare("int")) || (!type.compare("float")) ||
      (!type.compare("long"))) {
    length = 4;
  } else if (!type.compare("char")) {
    length = 1;
  } else if (!type.compare("double")) {
    length = 8;
  }

  return std::to_string(length);
}

void Assembler::doFunctionCall(const SyntaxTreeNode* node) {
  if (node == nullptr) {
    return;
  }

  auto nextNode = node->getFirstSon();
  std::string funcName;
  std::vector<std::string> parameterList;

  while (nextNode != nullptr) {
    if (nextNode->getType() == TokenType::FUNCTION_NAME) {
      funcName = nextNode->getValue();
      if ((funcName.compare("scanf")) && (funcName.compare("printf"))) {
#ifdef DEBUG
        perror("function call only support scanf and printf!\n");
#endif  // DEBUG
        error(__FILE__, __FUNCTION__, __LINE__);
      }
    } else if (!nextNode->getValue().compare("CallParameterList")) {
      auto tmpNode = nextNode->getFirstSon();
      while (tmpNode != nullptr) {
        switch (tmpNode->getType()) {
          case TokenType::DIGIT_CONSTANT:
          case TokenType::STRING_CONSTANT: {
            std::string label =
                std::string("label_") + std::to_string(labelCount_);
            ++labelCount_;
            if (tmpNode->getType() == TokenType::STRING_CONSTANT) {
              auto line = label + ": .asciz \"" + tmpNode->getValue() + "\"";
              assFileHandler_.insert(line, SegmentType::DATA);
            } else {
#ifdef DEBUG
              perror(
                  "function call digtial constant paramter is not supported "
                  "yet!\n");
#endif  // DEBUG
              error(__FILE__, __FUNCTION__, __LINE__);
            }
            symbolTable_[label] = {{"type", "STRING_CONSTANT"},
                                   {"value", tmpNode->getValue()}};
            parameterList.push_back(label);
            break;
          }
          case TokenType::IDENTIFIER: {
            parameterList.push_back(tmpNode->getValue());
            break;
          }
          case TokenType::ADDRESS: {
            break;
          }
          default: {
#ifdef DEBUG
            std::string errorCode =
                tmpNode->getValue() + " " + tokenTypeToStr(tmpNode->getType());
            perror("this parameter type is not support: ");
            perror(errorCode.c_str());
            perror("\n");
#endif  // DEBUG
            error(__FILE__, __FUNCTION__, __LINE__);
          }
        }
        tmpNode = tmpNode->getRight();
      }
    }
    nextNode = nextNode->getRight();
  }

  if (!funcName.compare("printf")) {
    size_t num = 0;
    while (!parameterList.empty()) {
      auto elem = parameterList.back();
      parameterList.pop_back();
      if (!symbolTable_[elem]["type"].compare("STRING_CONSTANT")) {
        assFileHandler_.insert(std::string("pushl $") + elem,
                               SegmentType::TEXT);
        ++num;
      } else if (!symbolTable_[elem]["type"].compare("VARIABLE")) {
        auto fieldType = symbolTable_[elem]["field_type"];
        if (!fieldType.compare("int")) {
          assFileHandler_.insert(std::string("pushl ") + elem,
                                 SegmentType::TEXT);
          ++num;
        } else if (!fieldType.compare("float")) {
          assFileHandler_.insert(std::string("flds ") + elem,
                                 SegmentType::TEXT);
          assFileHandler_.insert("subl $8, %esp", SegmentType::TEXT);
          assFileHandler_.insert("fstpl (%esp)", SegmentType::TEXT);
          num += 2;
        } else {
#ifdef DEBUG
          perror("field type except int and float is not supported yet!\n");
#endif  // DEBUG
          error(__FILE__, __FUNCTION__, __LINE__);
        }
      } else {
#ifdef DEBUG
        perror("paramter type not supported in printf yet!\n");
#endif  // DEBUG
        error(__FILE__, __FUNCTION__, __LINE__);
      }
    }
    assFileHandler_.insert("call printf", SegmentType::TEXT);
    assFileHandler_.insert(
        std::string("add $") + std::to_string(num * 4) + ", %esp",
        SegmentType::TEXT);
  } else if (!funcName.compare("scanf")) {
    size_t num = 0;

    while (!parameterList.empty()) {
      auto elem = parameterList.back();
      parameterList.pop_back();
      auto parameterType = symbolTable_[elem]["type"];
      if ((!parameterType.compare("STRING_CONSTANT")) ||
          (!parameterType.compare("VARIABLE"))) {
        ++num;
        assFileHandler_.insert("pushl $" + elem, SegmentType::TEXT);
      } else {
#ifdef DEBUG
        perror("parameter type not supported in scanf!\n");
#endif  // DEBUG
        error(__FILE__, __FUNCTION__, __LINE__);
      }
    }
    assFileHandler_.insert("call scanf", SegmentType::TEXT);
    assFileHandler_.insert("add $" + std::to_string(num * 4) + ", %esp",
                           SegmentType::TEXT);
  }
}

void Assembler::doAssignment(const SyntaxTreeNode* node) {
  if (node == nullptr) {
    return;
  }

  auto nextNode = node->getFirstSon();
  if ((nextNode->getType() == TokenType::IDENTIFIER) &&
      (!(nextNode->getRight()->getValue().compare("Expression")))) {
    auto express = doExpression(nextNode->getRight());
    auto fieldType = symbolTable_[nextNode->getValue()]["field_type"];
    if (!fieldType.compare("int")) {
      if (!express["type"].compare("CONSTANT")) {
        assFileHandler_.insert(
            "movl $" + express["value"] + ", " + nextNode->getValue(),
            SegmentType::TEXT);
      } else if (!express["type"].compare("VARIABLE")) {
        assFileHandler_.insert("movl " + express["value"] + ", " + "%edi",
                               SegmentType::TEXT);
        assFileHandler_.insert("movl %edi, " + nextNode->getValue(),
                               SegmentType::TEXT);
      } else {
      }
    } else if (!fieldType.compare("float")) {
      if (!express["type"].compare("CONSTANT")) {
        assFileHandler_.insert(
            "movl $" + express["value"] + ", " + nextNode->getValue(),
            SegmentType::TEXT);
        assFileHandler_.insert("filds " + nextNode->getValue(),
                               SegmentType::TEXT);
        assFileHandler_.insert("fstps " + nextNode->getValue(),
                               SegmentType::TEXT);
      } else {
        assFileHandler_.insert("fstps " + nextNode->getValue(),
                               SegmentType::TEXT);
      }
    } else {
#ifdef DEBUG
      perror("field type except int and float not supported!\n");
#endif  // DEBUG
      error(__FILE__, __FUNCTION__, __LINE__);
    }
  } else {
#ifdef DEBUG
    perror("assignment wrong\n");
#endif  // DEBUG
    error(__FILE__, __FUNCTION__, __LINE__);
  }
}

std::unordered_map<std::string, std::string> Assembler::doExpression(
    const SyntaxTreeNode* node) {}