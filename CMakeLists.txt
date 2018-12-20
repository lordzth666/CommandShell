cmake_minimum_required(VERSION 3.10)
project(CShell)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-pedantic -Wall -Werror -ggdb3 -O3 -DNOLIMIT -DSPREDUND -DCOLORED_OUTPUT")
# find header & source
file(GLOB_RECURSE HEADER "include/*.hpp")
file(GLOB_RECURSE SOURCE "src/*.cpp")

set(libcshell cshell)

add_library(${libcshell} ${HEADER} ${SOURCE})

add_executable(csh application/csh.cpp)
target_link_libraries(csh ${libcshell})

add_executable(performance application/performance.cpp)
target_link_libraries(performance ${libcshell})
