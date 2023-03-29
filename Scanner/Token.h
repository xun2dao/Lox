#pragma once
#include <sstream>
#include <string>

enum TokenType {
  // one character token
  _LEFT_PARENT,
  _RIGHT_PARENT,
  _LEFT_BRACE,
  _RIGHT_BRACE,
  _PLUS,
  _MINUS,
  _STAR,
  _SLASH,
  _COMMA,
  _SEMICOLON,
  _DOT,
  // one or two characters token for comparions
  _EQUAL,
  _EQUAL_EQUAL,
  _BANG,
  _BANG_EQUAL,
  _LESS,
  _LESS_EQUAL,
  _GREATER,
  _GREATER_EQUAL,

  // keywords
  _WHILE,
  _FOR,
  _IF,
  _ELSE,
  _AND,
  _OR,
  _THIS,
  _SUPER,
  _PRINT,
  _TRUE,
  _FALSE,
  _RETURN,
  _CLASS,
  _FUN,
  _VAR,
  _EOF,
  _EXIT
};

class Token {
private:
  TokenType m_type;
  int m_line;
  int m_begin;
  int m_length;
  std::string m_literal;

public:
  Token(TokenType type, int line, int begin, int length,
        std::string literal = "")
      : m_type(type), m_line(line), m_begin(begin), m_length(length),
        m_literal(literal) {}

  // little trick
  std::string ToString() const;
};
