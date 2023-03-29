#include "Token.h"
#include <sstream>
std::string Token::ToString() const {
  std::stringstream out;
  switch (m_type) {
#define SubType(x)                                                             \
  case TokenType::x:                                                           \
    out << #x << ":line_" << m_line << ": [" << m_begin << ","                 \
        << (m_begin + m_length - 1) << "]";                                    \
    return out.str();                                                          \
    break

    SubType(_LEFT_PARENT);
    SubType(_RIGHT_PARENT);
    SubType(_LEFT_BRACE);
    SubType(_RIGHT_BRACE);
    SubType(_PLUS);
    SubType(_MINUS);
    SubType(_STAR);
    SubType(_SLASH);
    SubType(_COMMA);
    SubType(_SEMICOLON);
    SubType(_DOT);
    SubType(_EQUAL);
    SubType(_EQUAL_EQUAL);
    SubType(_BANG);
    SubType(_BANG_EQUAL);
    SubType(_LESS);
    SubType(_LESS_EQUAL);
    SubType(_GREATER);
    SubType(_GREATER_EQUAL);
    SubType(_FOR);
    SubType(_IF);
    SubType(_ELSE);
    SubType(_AND);
    SubType(_OR);
    SubType(_THIS);
    SubType(_SUPER);
    SubType(_PRINT);
    SubType(_TRUE);
    SubType(_FALSE);
    SubType(_RETURN);
    SubType(_CLASS);
    SubType(_FUN);
    SubType(_VAR);
    SubType(_WHILE);
    SubType(_EOF);
    SubType(_EXIT);
#undef SubType
  default:
    return "Error Type";
  }
}
