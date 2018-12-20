#include <cstdlib>
#include <iostream>

int main(int argc, char ** argv) {
  if (argc == 1) {
    std::string istr;
    std::getline(std::cin, istr);
    std::cout << "I have size " << istr.size() << "." << std::endl;
    return EXIT_SUCCESS;
  }
  if (argc != 2) {
    std::cerr << "Usage: ./test_length [string](optional)" << std::endl;
    return EXIT_FAILURE;
  }
  std::string istr(argv[1]);
  std::cout << "I have size " << istr.size() << "." << std::endl;
  return EXIT_SUCCESS;
}
