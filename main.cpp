#include "Scanner/Scanner.h"
#include "Scanner/Token.h"
#include "error_reporter.h"
#include "utility/exceptions.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

bool g_hadError = false;
bool g_Stop = false;

void run(std::string code) {
  // Process Tokens
  std::cout << "code is : " << code << std::endl;
  Scanner scanner(code);
  scanner.Scan();
  scanner.Print();
}

static void runfile(std::string filename) {
  std::ifstream ifs(filename);
  if (!ifs.is_open())
    throw file_not_exist(filename);

  std::string source_code;
  while (ifs) {
    std::string line;
    // fs >> line; // 这种方式会按照空格输出
    std::getline(ifs, line);
    source_code += line + "\n";
  }
  run(source_code);
  if (g_hadError)
    exit(-1); // 如果存在代码错误，就要退出程序。
}

static void runprompt() {
  std::string line;
  for (; !g_Stop;) {
    std::cout << "> ";
    getline(std::cin, line);
    if (line.empty())
      break;
    run(line);
    g_hadError = false; // don't exit the session.
  }
}

int main(int argc, char **argv) {
  if (argc > 2) {
    std::cerr << "Usage: Lox [file]";
    exit(-1);
  } else if (argc == 2) {
    std::cout << "read source code from " << argv[1] << std::endl;
    try {
      runfile(argv[1]);
    } catch (std::exception &e) {
      std::cout << e.what() << std::endl;
      exit(-1);
    }
  } else {
    std::cout << "Command Line:" << std::endl;
    runprompt();
  }
  return 0;
}
