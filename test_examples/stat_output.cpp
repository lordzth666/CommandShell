#include <cstdlib>
#include <fstream>
#include <iostream>

int main(int argc, char ** argv) {
  if (argc > 3) {
    std::cerr << "usage: ./stat_output [filename] (optional)" << std::endl;
    return EXIT_FAILURE;
  }
  if (argc == 1) {
    size_t cnt = 0;
    while (1) {
      std::string i_str;
      std::getline(std::cin, i_str);
      if (!std::cin.good())
        break;
      cnt++;
    }
    std::cout << "I have " << cnt << " lines." << std::endl;
  }
  else {
    std::ifstream ifs(argv[1]);
    size_t cnt = 0;
    while (1) {
      std::string i_str;
      std::getline(ifs, i_str);
      if (!ifs.good())
        break;
      cnt++;
    }
    std::cout << "I have " << cnt << " lines." << std::endl;

    ifs.close();
  }

  return EXIT_SUCCESS;
}
