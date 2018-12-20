#include <cstdlib>
#include <fstream>
#include <iostream>

int main(int argc, char ** argv) {
  if (argc > 2) {
    std::cerr << "Usage: 04_test_echo [filename](optional)" << std::endl;
    return EXIT_FAILURE;
  }
  if (argc == 2) {
    std::ifstream ifs(argv[1], std::ios::in);
    std::string r_str;
    while (ifs.good()) {
      std::getline(ifs, r_str);
      if (!ifs.good())
        break;
      std::cout << r_str << std::endl;
    }
  }
  else {
    std::string r_str;
    while (std::cin.good()) {
      std::getline(std::cin, r_str);
      if (!std::cin.good())
        break;
      std::cout << r_str << std::endl;
    }
  }
  return EXIT_SUCCESS;
}
