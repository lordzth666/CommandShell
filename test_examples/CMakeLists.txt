cmake_minimum_required(VERSION 3.10)
project(CShell_test_cpp)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-pedantic -Wall -Werror ")

add_executable(inf_loop test_inf_loop.cpp)
add_executable(seg_fault test_segfault.cpp)
add_executable(test_arg test_arg.cpp)
add_executable(test_argcnt test_argcnt.cpp)
add_executable(test_length test_length.cpp)
add_executable(test_echo test_echo.cpp)
add_executable(random_generator random_generator.cpp)
add_executable(range_generator range_generator.cpp)

# functional testcases
add_executable(hello_world hello_world.cpp)
add_executable(grep_prime grep_prime.cpp)
add_executable(stat_output stat_output.cpp)
