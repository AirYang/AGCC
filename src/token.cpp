#include "../include/token.h"

const char *TokenLocation::Begin() const { return lineBegin_ + col_ - 1; }

const std::unordered_map<std::string, Token::TokenType> Token::kwTypeMap_{
    {"auto", Token::TokenType::AUTO},
    {"break", Token::TokenType::BREAK},
    {"case", Token::TokenType::CASE},
    {"char", Token::TokenType::CHAR},
    {"const", Token::TokenType::CONST},
    {"continue", Token::TokenType::CONTINUE},
    {"default", Token::TokenType::DEFAULT},
    {"do", Token::TokenType::DO},
    {"double", Token::TokenType::DOUBLE},
    {"else", Token::TokenType::ELSE},
    {"enum", Token::TokenType::ENUM},
    {"extern", Token::TokenType::EXTERN},
    {"float", Token::TokenType::FLOAT},
    {"for", Token::TokenType::FOR},
    {"goto", Token::TokenType::GOTO},
    {"if", Token::TokenType::IF},
    {"inline", Token::TokenType::INLINE},
    {"int", Token::TokenType::INT},
    {"long", Token::TokenType::LONG},
    {"signed", Token::TokenType::SIGNED},
    {"unsigned", Token::TokenType::UNSIGNED},
    {"register", Token::TokenType::REGISTER},
    {"restrict", Token::TokenType::RESTRICT},
    {"return", Token::TokenType::RETURN},
    {"short", Token::TokenType::SHORT},
    {"sizeof", Token::TokenType::SIZEOF},
    {"static", Token::TokenType::STATIC},
    {"struct", Token::TokenType::STRUCT},
    {"switch", Token::TokenType::SWITCH},
    {"typedef", Token::TokenType::TYPEDEF},
    {"union", Token::TokenType::UNION},
    {"void", Token::TokenType::VOID},
    {"volatile", Token::TokenType::VOLATILE},
    {"while", Token::TokenType::WHILE},
    {"_Alignas", Token::TokenType::ALIGNAS},
    {"_Alignof", Token::TokenType::ALIGNOF},
    {"_Atomic", Token::TokenType::ATOMIC},
    {"__attribute__", Token::TokenType::ATTRIBUTE},
    {"_Bool", Token::TokenType::BOOL},
    {"_Complex", Token::TokenType::COMPLEX},
    {"_Generic", Token::TokenType::GENERIC},
    {"_Imaginary", Token::TokenType::IMAGINARY},
    {"_Noreturn", Token::TokenType::NORETURN},
    {"_Static_assert", Token::TokenType::STATIC_ASSERT},
    {"_Thread_local", Token::TokenType::THREAD},
};

const std::unordered_map<Token::TokenType, std::string> Token::tagLexemeMap_{
    {Token::TokenType::LPAR, "("},
    {Token::TokenType::RPAR, ")"},
    {Token::TokenType::LSQB, "["},
    {Token::TokenType::RSQB, "]"},
    {Token::TokenType::COLON, ":"},
    {Token::TokenType::COMMA, ","},
    {Token::TokenType::SEMI, ";"},
    {Token::TokenType::ADD, "+"},
    {Token::TokenType::SUB, "-"},
    {Token::TokenType::MUL, "*"},
    {Token::TokenType::DIV, "/"},
    {Token::TokenType::OR, "|"},
    {Token::TokenType::AND, "&"},
    {Token::TokenType::LESS, "<"},
    {Token::TokenType::GREATER, ">"},
    {Token::TokenType::EQUAL, "="},
    {Token::TokenType::DOT, "."},
    {Token::TokenType::MOD, "%"},
    {Token::TokenType::LBRACE, "{"},
    {Token::TokenType::RBRACE, "}"},
    {Token::TokenType::XOR, "^"},
    {Token::TokenType::TILDE, "~"},
    {Token::TokenType::NOT, "!"},
    {Token::TokenType::COND, "?"},
    {Token::TokenType::SHARP, "#"},

    {Token::TokenType::DSHARP, "##"},
    {Token::TokenType::PTR, "->"},
    {Token::TokenType::INC, "++"},
    {Token::TokenType::DEC, "--"},
    {Token::TokenType::LEFT, "<<"},
    {Token::TokenType::RIGHT, ">>"},
    {Token::TokenType::LE, "<="},
    {Token::TokenType::GE, ">="},
    {Token::TokenType::EQ, "=="},
    {Token::TokenType::NE, "!="},
    {Token::TokenType::LOGICAL_AND, "&&"},
    {Token::TokenType::LOGICAL_OR, "||"},
    {Token::TokenType::MUL_ASSIGN, "*="},
    {Token::TokenType::DIV_ASSIGN, "/="},
    {Token::TokenType::MOD_ASSIGN, "%="},
    {Token::TokenType::ADD_ASSIGN, "+="},
    {Token::TokenType::SUB_ASSIGN, "-="},
    {Token::TokenType::LEFT_ASSIGN, "<<="},
    {Token::TokenType::RIGHT_ASSIGN, ">>="},
    {Token::TokenType::AND_ASSIGN, "&="},
    {Token::TokenType::XOR_ASSIGN, "^="},
    {Token::TokenType::OR_ASSIGN, "|="},
    {Token::TokenType::ELLIPSIS, "..."},

    {Token::TokenType::AUTO, "auto"},
    {Token::TokenType::BREAK, "break"},
    {Token::TokenType::CASE, "case"},
    {Token::TokenType::CHAR, "char"},
    {Token::TokenType::CONST, "const"},
    {Token::TokenType::CONTINUE, "continue"},
    {Token::TokenType::DEFAULT, "default"},
    {Token::TokenType::DO, "do"},
    {Token::TokenType::DOUBLE, "double"},
    {Token::TokenType::ELSE, "else"},
    {Token::TokenType::ENUM, "enum"},
    {Token::TokenType::EXTERN, "extern"},
    {Token::TokenType::FLOAT, "float"},
    {Token::TokenType::FOR, "for"},
    {Token::TokenType::GOTO, "goto"},
    {Token::TokenType::IF, "if"},
    {Token::TokenType::INLINE, "inline"},
    {Token::TokenType::INT, "int"},
    {Token::TokenType::LONG, "long"},
    {Token::TokenType::SIGNED, "signed"},
    {Token::TokenType::UNSIGNED, "unsigned"},
    {Token::TokenType::REGISTER, "register"},
    {Token::TokenType::RESTRICT, "restrict"},
    {Token::TokenType::RETURN, "return"},
    {Token::TokenType::SHORT, "short"},
    {Token::TokenType::SIZEOF, "sizeof"},
    {Token::TokenType::STATIC, "static"},
    {Token::TokenType::STRUCT, "struct"},
    {Token::TokenType::SWITCH, "switch"},
    {Token::TokenType::TYPEDEF, "typedef"},
    {Token::TokenType::UNION, "union"},
    {Token::TokenType::VOID, "void"},
    {Token::TokenType::VOLATILE, "volatile"},
    {Token::TokenType::WHILE, "while"},
    {Token::TokenType::ALIGNAS, "_Alignas"},
    {Token::TokenType::ALIGNOF, "_Alignof"},
    {Token::TokenType::ATOMIC, "_Atomic"},
    {Token::TokenType::ATTRIBUTE, "__attribute__"},
    {Token::TokenType::BOOL, "_Bool"},
    {Token::TokenType::COMPLEX, "_Complex"},
    {Token::TokenType::GENERIC, "_Generic"},
    {Token::TokenType::IMAGINARY, "_Imaginary"},
    {Token::TokenType::NORETURN, "_Noreturn"},
    {Token::TokenType::STATIC_ASSERT, "_Static_assert"},
    {Token::TokenType::THREAD, "_Thread_local"},

    {Token::TokenType::END, "(eof)"},
    {Token::TokenType::IDENTIFIER, "(identifier)"},
    {Token::TokenType::CONSTANT, "(constant)"},
    {Token::TokenType::LITERAL, "(string literal)"},
};

Token::TokenType Token::KeyWordTag(const std::string &key) {
  auto kwIter = kwTypeMap_.find(key);
  if (kwTypeMap_.end() == kwIter) return Token::NOTOK;  // not a key word type
  return kwIter->second;
}

bool Token::IsKeyWord(const Token::TokenType &tag) {
  return TokenType::CONST <= tag && tag < TokenType::IDENTIFIER;
}

std::string Token::Lexeme(const TokenType &tag) {
  auto iter = tagLexemeMap_.find(tag);
  if (iter == tagLexemeMap_.end()) return nullptr;

  return iter->second;
}

bool Token::isKeyWord() const { return IsKeyWord(tag_); }

bool Token::isPunctuator() const {
  return 0 <= tag_ && tag_ <= TokenType::ELLIPSIS;
}

bool Token::isLiteral() const { return tag_ == TokenType::LITERAL; }

bool Token::isConstant() const {
  return TokenType::CONSTANT <= tag_ && tag_ <= TokenType::F_CONSTANT;
}

bool Token::isIdentifier() const { return TokenType::IDENTIFIER == tag_; }

bool Token::isEOF() const { return tag_ == TokenType::END; }

bool Token::isTypeSpecQual() const {
  return TokenType::CONST <= tag_ && tag_ <= TokenType::ENUM;
}

bool Token::isDecl() const {
  return TokenType::CONST <= tag_ && tag_ <= TokenType::REGISTER;
}

Token &Token::operator=(const Token &other) {
  tag_ = other.tag_;
  loc_ = other.loc_;
  whiteSpace_ = other.whiteSpace_;
  str_ = other.str_;
  ss_ = (other.ss_ != nullptr) ? new StrSet(*other.ss_) : nullptr;
  return *this;
}

Token::Token(TokenType tag) : tag_(tag) {}

Token::Token(TokenType tag, const TokenLocation &loc) : tag_(tag), loc_(loc) {}

Token::Token(const Token &other) { *this = other; }

TokenContainer::TokenContainer()
    : tokenList_(new TokenList()),
      begin_(tokenList_->begin()),
      end_(tokenList_->end()) {}

TokenContainer::TokenContainer(Token *tok) {
  TokenContainer();
  insertBack(tok);
}

TokenContainer::TokenContainer(TokenList *tokList)
    : tokenList_(tokList), begin_(tokList->begin()), end_(tokList->end()) {}

TokenContainer::TokenContainer(TokenList *tokList, TokenList::iterator begin,
                               TokenList::iterator end)
    : tokenList_(tokList), begin_(begin), end_(end) {}

TokenContainer::TokenContainer(const TokenContainer &other) { *this = other; }

const TokenContainer &TokenContainer::operator=(const TokenContainer &other) {
  tokenList_ = other.tokenList_;
  begin_ = other.begin_;
  end_ = other.end_;
  return *this;
}

void TokenContainer::copy(const TokenContainer &other) {
  tokenList_ = new TokenList(other.begin_, other.end_);
  begin_ = tokenList_->begin();
  end_ = tokenList_->end();
  for (auto iter = begin_; iter != end_; ++iter) {
    *iter = new Token(**iter);
  }
}

void TokenContainer::insertBack(const Token *tok) {
  auto pos = tokenList_->insert(end_, tok);
  if (begin_ == end_) {
    pos = begin_;
  }
}
