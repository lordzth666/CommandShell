
#include "../include/Environment.hpp"

#include <iostream>
namespace Cshell {
  // Initialize and add the import environment variable
  Environment::Environment() {
    size = 0;
    FetchEnv("PATH");
    FetchEnv("USER");
    FetchEnv("PWD");
    FetchEnv("HOME");
    FetchEnv("LS_COLORS");
    //FetchEnv("DESKTOP_SESSION");
  }

  // @ FetchEnv
  // Fetch the environment variable of name and add it to the environment variable list
  // * Parameters
  // name: name of the desired environment variable
  // * Returns
  // void
  void Environment::FetchEnv(const char * name) {
    char * temp = getenv(name);
    std::string k_tmp(name);
    std::string v_tmp(temp);
    if (GetEnv(name) != "") {
      SetEnv(name, temp);
      return;
    }
    key.push_back(k_tmp);
    value.push_back(v_tmp);
    cast.push_back(true);
    size += 1;
  }

  // @ GetSize
  // Get the size of environment variable list
  // * Returns
  // int: size of environment variable list
  int Environment::GetSize() const { return (int)size; }

  // @ GetEnv
  // Get the environment variable of name from the environment variable list
  // * Parameters
  // name: name of the desired environment variable
  // * Returns
  // std::string: corresponding value of the environment variable
  std::string Environment::GetEnv(const char * name) const {
    std::string result;
    size_t v_size = size;
    std::string cmp_name(name);
    for (size_t i = 0; i < v_size; i++) {
      if (key[i] == cmp_name) {
        result = value[i];
        break;
      }
    }
    return result;
  }

  // @ PrintEnv
  // Print the value of desired variables in the variable list
  // * Parameters
  // name: name of the desired environment variable
  // * Returns
  // void
  void Environment::PrintEnv(const char * name) const {
    std::string cmp_str(name);
    size_t v_size = size;
    size_t index = v_size + 1;
    for (size_t i = 0; i < v_size; i++) {
      if (name == key[i]) {
        index = i;
        break;
      }
    }
    if (index == v_size + 1)
      std::cerr << "Error! Environment Variable not Found!" << std::endl;
    else
      std::cout << value[index];
  }

  // Add color support

  void Environment::PrintEnv(const char * name, const std::string & color) const {
    std::string cmp_str(name);
    size_t v_size = size;
    size_t index = v_size + 1;
    for (size_t i = 0; i < v_size; i++) {
      if (name == key[i]) {
        index = i;
        break;
      }
    }
    if (index == v_size + 1)
      std::cerr << "Error! Environment Variable not Found!" << std::endl;
    else
      std::cout << format_bold_color_output(value[index], color);
  }

  // @ SetEnv
  // Set the desired environment variable
  // * Parameters
  // name: name of the desired environment variable
  // values: value to be set
  // * Returns
  // void
  void Environment::SetEnv(const char * name, const char * values) {
    std::string name_str(name);
    std::string value_str(values);
    for (size_t i = 0; i < size; i++) {
      if (key[i] == name_str) {
        value[i] = value_str;
        return;
      }
    }
    value.push_back(value_str);
    key.push_back(name_str);
    cast.push_back(false);
    size += 1;
  }

  // overloaded for std::string value_str
  void Environment::SetEnv(const char * name, const std::string & value_str) {
    std::string name_str(name);
    for (size_t i = 0; i < size; i++) {
      if (key[i] == name_str) {
        value[i] = value_str;
        return;
      }
    }
    value.push_back(value_str);
    key.push_back(name_str);
    cast.push_back(false);
    size += 1;
  }

  // @ ExportAllEnv
  // Print all the exported environment variables
  // * Returns
  // void
  void Environment::ExportAllEnv() {
    for (size_t i = 0; i < size; i++) {
      if (cast[i])
        std::cout << key[i] << " = " << value[i] << std::endl;
    }
  }

  // @ ExportEnv
  // Export a specific environment variable
  // * Paremeters
  // name: name of the desired environment variable
  // * Returns
  // void
  void Environment::ExportEnv(const char * name) {
    std::string name_str(name);
    for (size_t i = 0; i < size; i++) {
      if (key[i] == name_str) {
        cast[i] = true;
        return;
      }
    }
  }

  // @ Add_Alias
  // Add an alias item
  // * Paremeters
  // line: alias to be added
  // * Returns
  // void
  void Environment::Add_Alias(std::string line) {
    size_t pos = line.find("=");
    std::pair<std::string, std::string> item_i(line.substr(0, pos),
                                               line.substr(pos + 1, line.size() - pos));
    size_t l = alias.size();
    for (size_t i = 0; i < l; i++) {
      if (alias[i].first == item_i.first) {
        alias[i].second = item_i.second;
        return;
      }
    }
    alias.push_back(item_i);
  }

  // @ Find_Alias
  // Find an alias item and returns the corresponding content
  // * Paremeters
  // var: alias item name to be found
  // * Returns
  // std::string: corresponding content
  std::string Environment::Find_Alias(std::string var) {
    size_t l = alias.size();
    for (size_t i = 0; i < l; i++) {
      if (alias[i].first == var)
        return alias[i].second;
    }
    return "";
  }

  // @ CheckEnvMisc
  // sustitute $VAR with its actual value in a command line
  // * Paremeters
  // r_str: command line to be substituted
  // * Returns
  // std::string: substituted line
  std::string Environment::CheckEnvMisc(std::string r_str) {
    char sentinel = '\0';
    size_t i = 0;
    r_str += '/';
    size_t l = r_str.size();
    while (builtin::is_char_separator(r_str[i])) {
      i++;
    }
    size_t first_char_pos = i;
    while (i < l) {
      if ((r_str[i] == '~') && (i == first_char_pos)) {
        std::string home_str = GetEnv("HOME");
        r_str.replace(i, 1, home_str);
        continue;
      }
      if (r_str[i] != '$') {
        i++;
        continue;
      }
      else {
        size_t j = i + 1;
        if (builtin::is_sh_bracket(r_str[j])) {
          sentinel = r_str[j];
          j++;
        }
        std::string var;
        while (((r_str[j] != '/') && (!builtin::is_special_env_header(r_str[j])) &&
                (!builtin::is_pair_bracket(sentinel, r_str[j]))) &&
               (j < l)) {
          var += r_str[j];
          j++;
        }
        if (j == l)
          break;
        if (builtin::is_special_env_header(r_str[j]))
          j += 0;
        else if (builtin::is_pair_bracket(sentinel, r_str[j]))
          j++;
        std::string env_str = GetEnv(var.c_str());
        r_str.replace(i, j - i, env_str);
        sentinel = '\0';
      }
      l = r_str.size();
    }
    r_str.pop_back();

    return r_str;
  }
}  // namespace Cshell
