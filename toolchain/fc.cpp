#include <cstdlib>
#include <fstream>
#include <iostream>

int main(int argc, char ** argv) {
  if (argc < 3) {
    std::cerr << "Usage: ./fc [filename1] [filename2] --show-diff-kinds=all(optional)" << std::endl;
    return EXIT_FAILURE;
  }
  bool show_all_diff = false;
  if (argc > 3) {
    std::string cmd(argv[3]);
    if (cmd == "--show-diff-kinds=all")
      show_all_diff = true;
    else {
      std::cerr << argv[3] << ": Unrecognized argument." << std::endl;
      return EXIT_FAILURE;
    }
  }

  std::ifstream ifs_s(argv[1], std::ios::in);
  if (ifs_s.fail()) {
    std::cerr << "Error: " << argv[1] << " not found." << std::endl;
    return EXIT_FAILURE;
  }
  std::ifstream ifs_d(argv[2], std::ios::in);
  if (ifs_d.fail()) {
    std::cerr << "Error: " << argv[2] << " not found." << std::endl;
    return EXIT_FAILURE;
  }
  size_t ln = 0;
  while (1) {
    ln++;
    std::string s_str;
    std::string d_str;
    std::getline(ifs_s, s_str);
    std::getline(ifs_d, d_str);
    if ((!ifs_s.good()) && (!ifs_d.good()))
      break;
    if ((!ifs_s.good()) && (ifs_d.good())) {
      std::cout << argv[2] << " has lines after " << ln;
      if (show_all_diff) {
        while (1) {
          if (!ifs_d.good())
            break;
          std::cout << d_str << std::endl;
          std::getline(ifs_d, d_str);
        }
      }
      break;
    }
    if ((ifs_s.good()) && (!ifs_d.good())) {
      std::cout << argv[1] << " has lines after " << ln;
      if (show_all_diff) {
        while (1) {
          if (!ifs_s.good())
            break;
          std::cout << s_str << std::endl;
          std::getline(ifs_s, s_str);
        }
      }
      break;
    }
    if (s_str != d_str) {
      if (show_all_diff) {
        std::cout << argv[1] << " expects " << s_str << ", but " << argv[2] << " has " << d_str
                  << "." << std::endl;
      }
      else {
        std::cout << "Line " << ln << " is different." << std::endl;
      }
    }
  }
  ifs_s.close();
  ifs_d.close();
  return EXIT_SUCCESS;
}
