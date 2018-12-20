#include "../include/file.hpp"

namespace Cshell {
  // @ embed_path_and_filename
  // Add search path name to filename
  // * Parameters
  // path_vector: search path vectors
  // filename: executable name
  // * Returns
  // std::vector<std::string>: filenames with different search paths

  std::vector<std::string> embed_path_and_filename(const std::vector<std::string> & path_vector,
                                                   const char * filename) {
    std::vector<std::string> path_str_vector;
    std::string path_string;
    size_t pv_size = path_vector.size();
    for (size_t i = 0; i < pv_size; i++) {
      path_string = path_vector[i];
      if (!path_string.empty())
        if ((path_string[path_string.size() - 1] != '/'))
          path_string.push_back('/');
      path_str_vector.push_back(path_string + filename);
    }
    return path_str_vector;
  }

  int format_string(std::string & line) {
    std::string new_line;
    size_t l = line.size();
    size_t i = 0;
    while (i < l) {
      if (line[i] == '>') {
        if (i == l - 1)
          return 0;
        new_line += line[i];
        if (line[i + 1] == '>') {
          i++;
          new_line += line[i];
        }
        i++;
        while (builtin::is_char_separator(line[i])) {
          i++;
          if (i > l)
            return 0;
        }
        continue;
      }
      else if (line[i] == '<') {
        new_line += line[i];
        i++;
        while (builtin::is_char_separator(line[i])) {
          i++;
          if (i > l)
            return 0;
        }
        continue;
      }
      else {
        new_line += line[i];
      }
      i++;
    }
    line = new_line;
    return 1;
  }

}  // namespace Cshell
