#include <ctime>
#include <fstream>
#include <iostream>

#include "../include/Cshell.hpp"

#define TRIES 100
#define TESTSH "/home/tz86/ece551/mp_miniproject/run_performance.sh"

bool is_valid_cmd(std::string & str) {
  if (str.empty())
    return false;
  size_t i = 0;
  size_t l = str.size();
  while ((str[i] == ' ') || (str[i] == '\n') || (str[i] == '\t')) {
    i++;
    if (i == l)
      return false;
  }
  if (str[i] == '#')
    return false;
  else
    return true;
}

long get_lines(const char * fname) {
  long cnt = 0;
  std::ifstream ifs(fname, std::ios::in);
  std::string ifs_str;
  while (1) {
    std::getline(ifs, ifs_str);
    if (!ifs.good())
      break;
    if (is_valid_cmd(ifs_str))
      cnt++;
  }
  ifs.close();
  return cnt;
}

int main() {
  Cshell::Cshell csh;
  long cmd_number = get_lines("./cshrc");
  long start = clock();
  for (long i = 0; i < TRIES; i++) {
    csh.run_from_file(TESTSH);
  }
  long end = clock();
  std::cout << "I can execute " << cmd_number * TRIES / (float(end - start) / CLOCKS_PER_SEC)
            << " commands per second!" << std::endl;
}
