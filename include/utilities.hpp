#ifndef CSHELL_UTILITIES_HPP
#define CSHELL_UTILITIES_HPP

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>

#define RED "31"
#define GREEN "32"
#define YELLOW "33"
#define BLUE "34"
#define MAGENTA "35"

namespace Cshell {
  void wait_process(pid_t cpid);
  void close_all_stream();
  void shell_copy(const char * src, const char * dst);
  std::string format_color_output(const std::string & line, const std::string & color);
  std::string format_bold_color_output(const std::string & line, const std::string & color);

}  // namespace Cshell
#endif
