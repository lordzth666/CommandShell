cmake_minimum_required(VERSION 3.10)
project(CShell_tools)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-pedantic -Wall -Werror -DNOLIMIT -DHAVEFUN -DSPREDUND")

add_executable(fc fc.cpp)

