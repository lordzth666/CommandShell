#ifndef CSHELL_FILE_HPP
#define CSHELL_FILE_HPP

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "builtin.hpp"

namespace Cshell {
  std::vector<std::string> embed_path_and_filename(const std::vector<std::string> & path_vector,
                                                   const char * filename);

  int format_string(std::string & line);

}  // namespace Cshell
#endif  //CSHELL_FILE_HPP
