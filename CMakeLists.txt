cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
project(Lox)

#add_compile_definitions(DEBUG)
aux_source_directory(Scanner/ SRC)

add_executable(Lox main.cpp ${SRC})
