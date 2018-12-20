#ifndef CSHELL_BUILTIN_HPP
#define CSHELL_BUILTIN_HPP

#include <iostream>
#include <string>

namespace Cshell {
  namespace builtin {
    float to_float(const std::string & rhs);
    long to_int(const std::string & rhs);
    bool is_char_separator(char ch);
    bool is_pair_bracket(char sentinel, char ch);
    bool is_sh_bracket(char ch);
    bool is_special_env_header(char ch);
    bool is_valid_varname(std::string & rhs);
    long count_back_slash(const std::string & rhs);
  }  // namespace builtin
}  // namespace Cshell
#endif
