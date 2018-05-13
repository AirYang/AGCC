#include <unistd.h>

#include <cassert>
#include <cstdio>
#include <cstdlib>

#include <algorithm>
#include <string>

#include "../include/agcc.h"
#include "../include/error.h"
#include "../include/lexer.h"
#include "../include/parser.h"
#include "../include/syntax_tree.h"
#include "../include/token.h"
#include "../include/type.h"

AGCC::AGCC(int argc, char** argv)
    : fileName_(""),
      fileInput_(),
      needLexer_(false),
      needParser_(false),
      needAssembler_(false) {
  if (!paraInit(argc, argv)) {
    help();
#ifdef DEBUG
    perror("You must give a could be opened .c file\n");
#endif  // DEBUG
    error(__FILE__, __FUNCTION__, __LINE__);
  }
}

void AGCC::help() {
  std::string helpStr =
      "Compiler for C with C++\n"
      "\nUsage: ./AGCC -s [file] [options]\n"
      "\nOptions:\n  -h  show help\n  -s  file  import source file[.c "
      "required!]\n "
      " -l  lexer\n  -p  parser\n  -a  assembler[AT&T file]\n"
      "\nExample:\n  ./AGCC -h\n  ./AGCC -s source.c -a\n";
  printf("%s", helpStr.c_str());
}

bool AGCC::paraInit(int argc, char** argv) {
  for (int c; (c = getopt(argc, argv, "s:lpah")) != -1;) {
    switch (c) {
      case 's':
        fileName_ = std::string(optarg);
        fileInput_.open(fileName_);
        break;
      case 'l':
        needLexer_ = true;
        break;
      case 'p':
        needParser_ = true;
        break;
      case 'a':
        needAssembler_ = true;
        break;
      case 'h':
        help();
        exit(-1);
        break;
    }
  }
  return fileInput_.is_open();
}

void AGCC::printSyntaxTree(SyntaxTree* tree) {
  printf("------Syntax Tree Begin------\n");
  printf("%s", tree->toString());
  printf("------Syntax Tree End--------\n");
}

bool AGCC::run() {
  Lexer lexer(fileInput_);
  std::list<Token*> tokens = lexer.getTokens();
  if (needLexer_) {
    printf("------Lexer Begin------\n");
    std::for_each(tokens.begin(), tokens.end(), [](const Token* ctp) {
      assert(ctp != nullptr);
      printf("  %s\n", ctp->toString().c_str());
    });
    printf("------Lexer End--------\n");
  }
  return true;
}