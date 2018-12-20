#include "../include/builtin.hpp"

// namespace builtin
// small functions defined to avoid conflict with system namespace
namespace Cshell {
  namespace builtin {
    // convert string to int
    long to_int(const std::string & rhs) { return std::atoi(rhs.c_str()); }
    // decide if a character is a char separator
    bool is_char_separator(char ch) {
      if ((ch == '\n') || (ch == '\t') || (ch == ' '))
        return true;
      else
        return false;
    }
    // convert string to float
    float to_float(const std::string & rhs) { return std::atof(rhs.c_str()); }
    // pair bracket
    bool is_pair_bracket(char sentinel, char ch) {
      if ((sentinel == '(') && (ch == ')'))
        return true;
      if ((sentinel == '{') && (ch == '}'))
        return true;
      if ((sentinel == '[') && (ch == ']'))
        return true;
      return false;
    }
    // decide if a character is a shell bracket
    bool is_sh_bracket(char ch) { return ((ch == '(') || (ch == '[') || (ch == '{')); }

    // Check if it is a special environment header
    bool is_special_env_header(char ch) {
      if ((ch == '$') || (ch == '+') || (ch == '-') || (ch == '*') || (ch == ':'))
        return true;
      else
        return false;
    }

    // Check if the variable name is valid
    bool is_valid_varname(std::string & rhs) {
      size_t i = 0;
      size_t rhs_l = rhs.size();
      if (rhs_l == 0)
        return true;
      if ((rhs[0] >= '0') && (rhs[0] <= '9'))
        return false;
      while (i < rhs_l) {
        if (((rhs[i] >= '0') && (rhs[i] <= '9')) || ((rhs[i] >= 'a') && (rhs[i] <= 'z')) ||
            ((rhs[i] >= 'A') && (rhs[i] <= 'Z')) || (rhs[i] == '_')) {
          i++;
          continue;
        }
        else {
          return false;
        }
      }
      return true;
    }

    // Count back-slash
    long count_back_slash(const std::string & rhs) {
      if (rhs == "")
        return 0;
      long l = rhs.size();
      long i = l - 2;
      long res = 0;
      while (i >= 0) {
        if (rhs[i] == '\\')
          res++;
        else
          break;
        i--;
      }
      return res;
    }
  }  // namespace builtin
}  // namespace Cshell
