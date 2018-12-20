#include "../include/version.hpp"

#include <iostream>

namespace Cshell {
  void __VERSION() { std::cout << "Cshell " << VERSION << " On " << SYS_VER << std::endl; }
}  // namespace Cshell
