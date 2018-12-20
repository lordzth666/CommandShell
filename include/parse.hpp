#ifndef CSHELL_PARSE_HPP
#define CSHELL_PARSE_HPP

#include <string.h>

#include <iostream>
#include <set>
#include <string>
#include <vector>

#include "../include/builtin.hpp"

namespace Cshell {
  std::vector<std::string> parse_command(const std::string & cmd,
                                         std::set<size_t> & sp_c,
                                         std::vector<bool> & cast,
                                         int * argc);
  std::vector<std::string> unpack_path(const std::string & path);
  char ** remove_redirect(const std::vector<std::string> & argv, int * argc);

  std::string parse_special_char(const std::string & line, std::set<size_t> & sp_c);
  std::string parse_comment(const std::string & line);
  char lookup_special(char key);

  bool check_complete(const std::string & line);
  bool has_pipe(const std::string & line);
  bool check_empty(const std::string & line);

  std::vector<std::string> split_piped_command(const std::string & line);

  std::pair<long, std::string> parse_history(const std::string & line);
}  // namespace Cshell
#endif  //CSHELL_PARSE_HPP
