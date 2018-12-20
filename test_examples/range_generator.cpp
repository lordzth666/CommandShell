#include <cstdio>
#include <cstdlib>
#include <iostream>

int main(int argc, char ** argv) {
  if (argc != 2) {
    std::cerr << "Usage: ./range_generator [number]" << std::endl;
    return EXIT_FAILURE;
  }
  long n = std::atoi(argv[1]);
  for (long i = 0; i < n; i++) {
    std::cout << i << std::endl;
  }
  return EXIT_SUCCESS;
}
