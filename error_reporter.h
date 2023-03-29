#pragma once
#include <iostream>
extern bool g_hadError;
class ErrorReporter {
public:
  static void error(int line, std::string message) {
    report(line, "", message);
  }
  static void report(int line, std::string where, std::string message) {
    std::cout << "[" << line << "]" << where << ": " << message << std::endl;
    g_hadError = true;
  }
};
