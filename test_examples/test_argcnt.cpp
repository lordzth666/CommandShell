#include <cstdlib>
#include <iostream>

int main(int argc, char ** argv) {
  std::cout << "Oh I have " << argc - 1 << " input parameters!" << std::endl;
  return EXIT_SUCCESS;
}
