#include "../include/parse.hpp"

#include <malloc.h>

#define IS_NUMERIC(ch) ((ch >= '0') && (ch <= '9'))
namespace Cshell {
  // @ parse_command
  // Parse the input command and split them into argv
  // * Parameters
  // cmd: input command
  // argc: computed argument count
  // cast: check whether the argument needs to convert escape characters
  // * Returns
  // std::vector<std::string>: argv
  std::vector<std::string> parse_command(const std::string & cmd,
                                         std::set<size_t> & sp_c,
                                         std::vector<bool> & cast,
                                         int * argc) {
    std::string tmp;
    size_t l = cmd.size();
    size_t sz = 0;
    // used to set quote marks
    char sentinel = '\0';
    // determine whether we need to interpret escape characters
    bool non_escape = false;
    std::vector<std::string> argv;
    for (size_t i = 0; i < l; i++) {
      // parsing escape mode
      if (((cmd[i] == '\'') || ((cmd[i] == '\"')))) {
        if (sentinel == cmd[i]) {
          sentinel = '\0';
          continue;
        }
        if (!sentinel) {
          sentinel = cmd[i];
          if (cmd[i] == '\'')
            non_escape = true;
          continue;
        }
      }
      // Special case, handling escape ' and "
      if ((sentinel == '\"') && (cmd[i] == '\\')) {
        i++;
        tmp += cmd[i];
        continue;
      }
      if ((sentinel == '\'') && (cmd[i] == '\\')) {
        i++;
        tmp += '\\';
        tmp += cmd[i];
        continue;
      }

      // parsing pipe '|'
      if (cmd[i] == '|') {
        if (!tmp.empty()) {
          argv.push_back(tmp);
          cast.push_back(non_escape);
          non_escape = false;
          tmp = "";
        }
        argv.emplace_back("|");
        continue;
      }
      // parsing seperator
      if (((cmd[i] != '\t') && (cmd[i] != ' ') && (cmd[i] != '\n')) ||
          (sp_c.find(i) != sp_c.end())) {
        tmp += cmd[i];
      }
      else {
        if (sentinel == '\0') {
          if (tmp.empty())
            continue;
          sz += 1;
          argv.push_back(tmp);
          cast.push_back(non_escape);
          non_escape = false;
          tmp = "";
        }
        else {
          tmp += cmd[i];
        }
      }
    }
    // parsing the last argument
    if (!tmp.empty()) {
      sz += 1;
      argv.push_back(tmp);
      cast.push_back(non_escape);
      non_escape = false;
    }
    *argc = argv.size();
    return argv;
  }

  // @ unpack_path
  // Unpack the system paths according to the $PATH variable
  // * Parameters: path represents the $PATH variable
  // * Returns: std::vector<std::string> the unpacked path variables
  std::vector<std::string> unpack_path(const std::string & path) {
    std::vector<std::string> result;
    size_t str_size = path.size();
    std::string tmp;
    for (size_t i = 0; i < str_size; i++) {
      if (path[i] != ':')
        tmp.push_back(path[i]);
      else {
        result.push_back(tmp);
        tmp = "";
      }
    }
    if (!tmp.empty())
      result.push_back(tmp);
    return result;
  }

  // @ remove_redirect
  // Deal with the input/output/error redirection
  // Find redirection in argv and process redirection.
  // Called before execve()
  // * Parameters: argv is the processed argvs in command shell
  // * Returns: char ** processed redirected argvs, used for
  // next-step execve() call.
  char ** remove_redirect(const std::vector<std::string> & argv, int * argc) {
    char ** result = nullptr;
    result = (char **)malloc(sizeof(char *) * 1);
    int sz = 0;
    size_t argv_sz = argv.size();

    bool is_iredirect = false;
    bool is_oredirect = false;
    bool is_eredirect = false;

    for (size_t i = 0; i < argv_sz; i++) {
      // handle input redirect
      if (argv[i][0] == '<') {
        if (is_iredirect)
          continue;
        std::string fname = argv[i].substr(1, argv[i].size() - 1);
        if (!freopen(fname.c_str(), "r", stdin)) {
          std::cerr << fname << ": file not found." << std::endl;
          return nullptr;
        }
        is_iredirect = true;
        continue;
      }
      // handle append redirect
      if ((argv[i][0] == '>') && (argv[i][1] == '>')) {
        if (is_oredirect)
          continue;
        std::string fname = argv[i].substr(2, argv[i].size() - 2);
        if (!freopen(fname.c_str(), "a", stdout)) {
          std::cerr << fname << ": file not found." << std::endl;
          return nullptr;
        }
        is_oredirect = true;
        continue;
      }

      // handle output redirect
      if (argv[i][0] == '>') {
        if (is_oredirect)
          continue;
        std::string fname = argv[i].substr(1, argv[i].size() - 1);
        if (!freopen(fname.c_str(), "w", stdout)) {
          std::cerr << "IO error!" << std::endl;
          return nullptr;
        }
        is_oredirect = true;
        continue;
      }
      // handle error redirect
      if ((argv[i][0] == '2') && (argv[i][1] == '>')) {
        if (is_eredirect)
          continue;
        std::string fname = argv[i].substr(2, argv[i].size() - 2);
        if (!freopen(fname.c_str(), "w", stderr)) {
          std::cerr << "IO error!" << std::endl;
          return nullptr;
        }
        is_eredirect = true;
        continue;
      }
      // now split command
      sz += 1;
      result = (char **)realloc(result, sizeof(char *) * sz);
      result[sz - 1] = strdup(argv[i].c_str());
    }
    // entering the last piped command
    sz += 1;
    result = (char **)realloc(result, sizeof(char *) * sz);
    result[sz - 1] = nullptr;
    *argc = sz;
    return result;
  }

  // @ parse_special_char
  // Parse the escape characters in the current line
  // * Parameters
  // line: current line
  // sp_c: escape character location set
  // * Returns
  // std::string: processed line after the escape characters are parsed
  std::string parse_special_char(const std::string & line, std::set<size_t> & sp_c) {
    std::string result;
    size_t i = 0;
    size_t size = line.size();
    // skip seperator
    while (builtin::is_char_separator(line[i])) {
      i++;
      if (i == size)
        return line;
    }
    while (i < size) {
      // parsing non-esacpe characters
      if (line[i] == '\'') {
        result += line[i];
        i++;
        while (line[i] != '\'') {
          result += line[i];
          i++;
          if (i == size)
            return result;
        }
        result += line[i];
        i++;
        continue;
      }
      // parsing '\' character and corresponding escape characters
      if (line[i] != '\\') {
        result += line[i];
      }
      else {
        i++;
        if ((line[i] == '\'') || (line[i] == '\"') || (line[i] == '\\')) {
          result += '\\';
          result += line[i];
        }
        else {
          result += lookup_special(line[i]);
          sp_c.emplace(result.size() - 1);
        }
      }
      i++;
    }
    return result;
  }

  // @ lookup_special
  // return desired output for escape character
  // * Parameter
  // key: Input escape character
  // * Returns
  // char represents actual character(raw character)
  char lookup_special(char key) {
    switch (key) {
      case 'n':
        return '\n';
      case '\\':
        return '\\';
      case 't':
        return '\t';
      case '\'':
        return '\'';
      case '\"':
        return '\"';
      case ' ':
        return ' ';
      case 'b':
        return '\b';
      default: {
        std::cerr << "Warning: unknown pattern \\" << key << std::endl;
        return '\0';
      }
    }
  }

  // @ check_complete
  // Check if the current line is complete
  // * Parameters
  // line: current line
  // * Returns
  // bool: 1 if current line is complete, 0 if current line is not complete
  bool check_complete(const std::string & line) {
    if (line.empty())
      return true;
    std::string line2 = parse_comment(line);
    char sentinel = '\0';
    size_t i = 0;
    size_t l = line2.size();
    long cur_back_slash = 0;
    while (i < l) {
      if (((line[i] == '\"') && ((cur_back_slash % 2 == 0) || (sentinel == '\''))) ||
          ((line[i] == '\'') && ((cur_back_slash % 2 == 0) || (sentinel == '\'')))) {
        if (!sentinel)
          sentinel = line2[i];
        else if (sentinel == line2[i])
          sentinel = '\0';
      }
      if (line2[i] == '\\')
        cur_back_slash++;
      else
        cur_back_slash = 0;
      i++;
    }
    // check if the pipe is complete
    i = l - 1;
    while (builtin::is_char_separator(line2[i])) {
      i--;
      if (i < 0)
        return true;
    }
    if (line2[i] == '|') {
      return false;
    }
    return (sentinel == '\0');
  }

  // @ has_pipe
  // Check if the current line has pipe
  // * Parameters
  // line: current line
  // * Returns
  // bool: 1 if current line has a pipe, 0 if current line doesn't have a pipe
  bool has_pipe(const std::string & line) {
    size_t l = line.size();
    for (size_t i = 0; i < l; i++)
      if (line[i] == '|')
        return true;
    return false;
  }

  // @ check_empty
  // check if the current line is empty
  // * Parameters
  // line: current line
  // * Returns
  // bool: 1 if current line is empty, 0 if current line is not empty
  bool check_empty(const std::string & line) {
    size_t sz = line.size();
    size_t i = 0;
    while (i < sz) {
      if ((line[i] != ' ') && (line[i] != '\t') && (line[i] != '\n'))
        return false;
      i++;
    }
    return true;
  }

  // @ split_piped_command
  // split the piped command to consecutive commands without pipe
  // * Parameters
  // line: current command
  // * Returns
  // std::vector<std::string>: consecutive commands without pipe
  std::vector<std::string> split_piped_command(const std::string & line) {
    std::vector<std::string> commands;
    std::string tmp;
    size_t l = line.size();
    for (size_t i = 0; i < l; i++) {
      if (line[i] == '|') {
        if (!check_empty(tmp))
          commands.push_back(tmp);
        tmp.clear();
      }
      else {
        tmp += line[i];
      }
    }
    if (!check_empty(tmp))
      commands.push_back(tmp);
    return commands;
  }

  // @ parse_history
  // Parse lines from the default history log file (.csh_history)
  // * Parameters
  // line: current line from history log file
  // * Returns
  // std::pair<long, std::string>: (-1,"") if parse error, ([line_number], [command]) if parse success
  std::pair<long, std::string> parse_history(const std::string & line) {
    std::pair<long, std::string> pair;
    size_t i = 0;
    size_t l = line.size();
    while (!builtin::is_char_separator(line[i])) {
      i++;
      if (i == l) {
        std::cerr << "Parse error! Invalid history file!" << std::endl;
        pair.first = -1;
        pair.second = "";
        return pair;
      }
    }
    pair.first = std::atoi((line.substr(0, i)).c_str());
    pair.second = line.substr(i + 1, l - i);
    return pair;
  }

  // @ parse_comment
  // Parse comment from lines in the .sh(or shell executable) file
  // For example, 'echo "hello" #"world"' will be parsed to 'echo "hello"'
  // * Parameters
  // line: current line from .sh (or shell executable) file
  // * Returns
  // line without comment
  std::string parse_comment(const std::string & line) {
    std::string tmp = "";
    size_t l = line.size();
    size_t pos = line.find('#');
    if (pos > l)
      return line;
    if (pos == 0)
      return "";
    long i = pos - 1;
    while (builtin::is_char_separator(line[i])) {
      i--;
      if (i < 0)
        return "";
    }
    return line.substr(0, i + 1);
  }
}  // namespace Cshell
