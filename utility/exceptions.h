#pragma once
#include <exception>
#include <string>
class file_not_exist : public std::exception {
public:
  file_not_exist(std::string filename) : file_name(filename) {}
  virtual const char* what() const noexcept override{ // 继承操作
    return "file does not exist"; 
  }

private:
  std::string file_name;
};
