#include "Scanner.h"

extern bool g_Stop;
std::unordered_map<std::string, TokenType> Scanner::s_keywords;

void Scanner::ConsumeToken() {
  char c = Advance();
  PRINT(c);

  bool finish = false;

  switch (c) {
#define SINGLE_TOKEN(x, type)                                                  \
  case x:                                                                      \
    AddToken(type);                                                            \
    finish = true;                                                             \
    break

    SINGLE_TOKEN('(', TokenType::_LEFT_PARENT);
    SINGLE_TOKEN(')', TokenType::_RIGHT_PARENT);
    SINGLE_TOKEN('{', TokenType::_LEFT_BRACE);
    SINGLE_TOKEN('}', TokenType::_RIGHT_BRACE);
    SINGLE_TOKEN('*', TokenType::_STAR);
    SINGLE_TOKEN('+', TokenType::_PLUS);
    SINGLE_TOKEN('-', TokenType::_MINUS);
    SINGLE_TOKEN('/', TokenType::_SLASH);
    SINGLE_TOKEN(',', TokenType::_COMMA);
    SINGLE_TOKEN('.', TokenType::_DOT);
#undef SINGLE_TOKEN
  case ';':
    AddToken(TokenType::_SEMICOLON);
    finish = true;
    m_line++; //
    break;
  }
  if (finish)
    return;

#define SD(x, type)                                                            \
  if (c == x) {                                                                \
    if (!IsEnd()) {                                                            \
      if (Advance() == '=') {                                                  \
        AddToken(TokenType::_##type##_EQUAL);                                  \
      } else {                                                                 \
        m_current--;                                                           \
        AddToken(TokenType::_##type);                                          \
      }                                                                        \
      finish = true;                                                           \
    } else {                                                                   \
      ErrorReporter::report(m_line, "",                                        \
                            std::string("x") + " should have rvalue.");        \
    }                                                                          \
  } else

  SD('=', EQUAL)
  SD('>', GREATER)
  SD('<', LESS)
  SD('!', BANG)
#undef SD

  if (std::isspace(c)) {
    return;
  } else {
    if (isalpha(c) || c == '_') {
      while (!IsEnd() && (c = Advance()) && isalnum(c))
        ;
      IsEnd() ? m_current : m_current--;
      PRINT(m_start);
      PRINT(m_current);
      std::string token = m_srcCode.substr(m_start, m_current - m_start);
      PRINT(token);
      auto [yes, type] = IsKeyWord(token);
      if (yes) {
        AddToken(type, token); // passed token is optional.
        if(token == "exit")
            g_Stop = true;
      } else {
        AddToken(TokenType::_VAR, token);
      }
    }
  }
}
