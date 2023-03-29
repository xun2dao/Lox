#pragma once
#include "../error_reporter.h"
#include "../utility/utility.h"
#include "Token.h"
#include <iostream>
#include <list>
#include <string>
#include <unordered_map>

class Scanner {
private:
  std::list<Token> m_tokens;
  std::string m_srcCode;
  unsigned int m_current; // the location of current character.
  unsigned int m_line;    // the line of current token.
  unsigned int m_start;   // the start of token

  static std::unordered_map<std::string, TokenType> s_keywords;

private:
  bool IsEnd() { return m_current >= m_srcCode.size(); }
  char Advance() { return m_srcCode[m_current++]; }

  void AddToken(TokenType type, std::string literal = "") {
    m_tokens.push_back(
        Token(type, m_line, m_start, m_current - m_start, literal));
  }
  void ConsumeToken();
  std::tuple<bool, TokenType> IsKeyWord(std::string &str) {
    if (s_keywords.count(str))
      return {true, s_keywords[str]};
    return {false, TokenType::_EOF};
  }

public:
  Scanner(std::string src)
      : m_srcCode{src}, m_line{1}, m_start{0}, m_current{0} {

    s_keywords["while"] = TokenType::_WHILE;
    s_keywords["if"] = TokenType::_IF;
    s_keywords["else"] = TokenType::_ELSE;
    s_keywords["for"] = TokenType::_FOR;
    s_keywords["and"] = TokenType::_AND;
    s_keywords["or"] = TokenType::_OR;
    s_keywords["this"] = TokenType::_THIS;
    s_keywords["super"] = TokenType::_SUPER;
    s_keywords["print"] = TokenType::_PRINT;
    s_keywords["true"] = TokenType::_TRUE;
    s_keywords["false"] = TokenType::_FALSE;
    s_keywords["return"] = TokenType::_RETURN;
    s_keywords["class"] = TokenType::_CLASS;
    s_keywords["fun"] = TokenType::_FUN;
    s_keywords["var"] = TokenType::_VAR;
    s_keywords["exit"] = TokenType::_EXIT;
  }

  void Scan() {
    while (!IsEnd()) {
      ConsumeToken();
      m_start = m_current;
    }
    AddToken(TokenType::_EOF);
  }

  void Print() {
    for (auto &item : m_tokens) {
      std::cout << item.ToString() << " ";
    }
    std::cout << std::endl;
  }
};
