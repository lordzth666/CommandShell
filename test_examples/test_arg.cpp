#include <cstdlib>
#include <iostream>

int main(int argc, char ** argv) {
  if (argc != 2) {
    std::cerr << "Usage: ./test_arg [parameter]" << std::endl;
    return EXIT_FAILURE;
  }
  int x;
  std::cin >> x;
  std::cout << x + 1 << std::endl;
  return EXIT_SUCCESS;
}
