#pragma once
#include <string>
#include<iostream>

namespace Utility {

static std::string ToUpper(std::string str) {
  std::string tmp;
  for (auto &c : str)
    tmp.push_back(toupper(c));
  return tmp;
}


#ifdef DEBUG
#define PRINT(x) std::cout<<#x<<" : "<<x<<std::endl 
#else
#define PRINT(x) 
#endif


} // namespace Utility
