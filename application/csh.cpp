#include "../include/Cshell.hpp"

int main(int argc, char ** argv) {
  if (argc > 2) {
    std::cerr << "Error: csh cannot take more than 2 arguments." << std::endl;
    std::cerr << "Usage: csh [filename](optional)" << std::endl;
    return EXIT_FAILURE;
  }
  Cshell::Cshell csh;
  if (argc == 1)
    csh.run();
  else {
    csh.run_from_file(argv[1]);
  }
  return EXIT_SUCCESS;
}
