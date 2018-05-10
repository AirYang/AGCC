#pragma once

#include <list>
#include <set>
#include <string>
#include <unordered_map>

class Token;
class Lexer;
class Front;
class Parser;

using StrSet = std::set<std::string>;
using TokenList = std::list<const Token *>;

class TokenLocation {
 public:
  const char *Begin() const;

 private:
  const std::string *fileName_;
  const char *lineBegin_;
  size_t row_;
  size_t col_;
};

class Token {
  friend class Lexer;

 public:
  enum TokenType {
    // Punctuators
    LPAR = '(',
    RPAR = ')',
    LSQB = '[',
    RSQB = ']',
    COLON = ':',
    COMMA = ',',
    SEMI = ';',
    ADD = '+',
    SUB = '-',
    MUL = '*',
    DIV = '/',
    OR = '|',
    AND = '&',
    XOR = '^',
    LESS = '<',
    GREATER = '>',
    EQUAL = '=',
    DOT = '.',
    MOD = '%',
    LBRACE = '{',
    RBRACE = '}',
    TILDE = '~',
    NOT = '!',
    COND = '?',
    SHARP = '#',
    NEW_LINE = '\n',

    DSHARP = 128,  //'##'
    PTR,
    INC,
    DEC,
    LEFT,
    RIGHT,
    LE,
    GE,
    EQ,
    NE,
    LOGICAL_AND,
    LOGICAL_OR,

    MUL_ASSIGN,
    DIV_ASSIGN,
    MOD_ASSIGN,
    ADD_ASSIGN,
    SUB_ASSIGN,
    LEFT_ASSIGN,
    RIGHT_ASSIGN,
    AND_ASSIGN,
    XOR_ASSIGN,
    OR_ASSIGN,

    ELLIPSIS,
    // Punctuators end

    // KEYWORD BEGIN
    // TYPE QUALIFIER BEGIN
    CONST,
    RESTRICT,
    VOLATILE,
    ATOMIC,
    // TYPE QUALIFIER END

    // TYPE SPECIFIER BEGIN
    VOID,
    CHAR,
    SHORT,
    INT,
    LONG,
    FLOAT,
    DOUBLE,
    SIGNED,
    UNSIGNED,
    BOOL,     //_Bool
    COMPLEX,  //_Complex
    STRUCT,
    UNION,
    ENUM,
    // TYPE SPECIFIER END

    ATTRIBUTE,  // GNU extension __attribute__
    // FUNCTION SPECIFIER BEGIN
    INLINE,
    NORETURN,  //_Noreturn
    // FUNCTION SPECIFIER END

    ALIGNAS,  //_Alignas
    // For syntactic convenience
    STATIC_ASSERT,  //_Static_assert
    // STORAGE CLASS SPECIFIER BEGIN
    TYPEDEF,
    EXTERN,
    STATIC,
    THREAD,  //_Thread_local
    AUTO,
    REGISTER,
    // STORAGE CLASS SPECIFIER END
    BREAK,
    CASE,
    CONTINUE,
    DEFAULT,
    DO,
    ELSE,
    FOR,
    GOTO,
    IF,
    RETURN,
    SIZEOF,
    SWITCH,
    WHILE,
    ALIGNOF,    //_Alignof
    GENERIC,    //_Generic
    IMAGINARY,  //_Imaginary
    // KEYWORD END

    IDENTIFIER,
    CONSTANT,  // 198
    I_CONSTANT,
    C_CONSTANT,
    F_CONSTANT,
    LITERAL,

    // For the parser, a identifier is a typedef name or user defined type
    POSTFIX_INC,
    POSTFIX_DEC,
    PREFIX_INC,
    PREFIX_DEC,
    ADDR,   // '&'
    DEREF,  // '*'
    PLUS,
    MINUS,
    CAST,

    // For preprocessor
    PP_IF,
    PP_IFDEF,
    PP_IFNDEF,
    PP_ELIF,
    PP_ELSE,
    PP_ENDIF,
    PP_INCLUDE,
    PP_DEFINE,
    PP_UNDEF,
    PP_LINE,
    PP_ERROR,
    PP_PRAGMA,
    PP_NONE,
    PP_EMPTY,

    IGNORE,
    INVALID,
    END,
    NOTOK = -1,
  };

 public:
  static TokenType KeyWordTag(const std::string &key);
  static bool IsKeyWord(const TokenType &tag);
  static std::string Lexeme(const TokenType &tag);

  bool isKeyWord() const;
  bool isPunctuator() const;
  bool isLiteral() const;
  bool isConstant() const;
  bool isIdentifier() const;
  bool isEOF() const;
  bool isTypeSpecQual() const;
  bool isDecl() const;

  Token &operator=(const Token &other);
  virtual ~Token() {}

  explicit Token(TokenType tag);
  Token(TokenType tag, const TokenLocation &loc);
  Token(const Token &other);

 public:
  TokenType tag_;
  TokenLocation loc_;
  bool whiteSpace_{false};
  std::string str_;
  StrSet *ss_{nullptr};

 private:
  static const std::unordered_map<std::string, TokenType> kwTypeMap_;
  static const std::unordered_map<TokenType, std::string> tagLexemeMap_;
};

class TokenContainer {
  friend class Front;

 public:
  TokenContainer();
  explicit TokenContainer(Token *tok);
  explicit TokenContainer(TokenList *tokList);
  TokenContainer(TokenList *tokList, TokenList::iterator begin,
                 TokenList::iterator end);
  TokenContainer(const TokenContainer &other);

  ~TokenContainer() {}

  const TokenContainer &operator=(const TokenContainer &other);

 public:
  void copy(const TokenContainer &other);
  void insertBack(const Token *tok);

 private:
  TokenList *tokenList_;
  mutable TokenList::iterator begin_;
  TokenList::iterator end_;
};