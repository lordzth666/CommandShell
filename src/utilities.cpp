#include "../include/utilities.hpp"
namespace Cshell {
  // @ wait_process
  // Wait for the fork() process to terminate
  // * Parameters
  // c_pid: process ID
  // * Returns
  // void
  void wait_process(pid_t cpid) {
    pid_t wait;
    int wstatus;
    do {
      wait = waitpid(cpid, &wstatus, WUNTRACED | WCONTINUED);
      if (wait == -1) {
        perror("Wait PID error!\n");
        exit(EXIT_FAILURE);
      }
      if (WIFEXITED(wstatus)) {
#ifdef SPREDUND
        if (WEXITSTATUS(wstatus) == 0) {
          break;
        }

#else
        if (WEXITSTATUS(wstatus) == 0) {
          std::cout << format_color_output("Program exited with status ", GREEN)
                    << format_color_output(std::to_string(WEXITSTATUS(wstatus)), GREEN)
                    << std::endl;
          break;
        }
#endif
        std::cout << format_color_output("Program exited with status ", RED)
                  << format_color_output(std::to_string(WEXITSTATUS(wstatus)), RED) << std::endl;
      }
      else if (WIFSIGNALED(wstatus)) {
        std::cout << format_color_output("Program is killed by signal ", RED)
                  << format_color_output(std::to_string(WTERMSIG(wstatus)), RED) << std::endl;
      }
      else if (WIFSTOPPED(wstatus)) {
        std::cout << format_color_output("Program is stopped by signal ", RED)
                  << format_color_output(std::to_string(WSTOPSIG(wstatus)), RED) << std::endl;
      }
      else if (WIFCONTINUED(wstatus)) {
        std::cout << format_color_output("Continued.", RED) << std::endl;
      }

    } while (!WIFEXITED(wstatus) && !WIFSIGNALED(wstatus));
  }

  // @ shell_copy
  // copy text files
  // * Parameters
  // src: source filename
  // dst: destination filename
  // * Returns
  // void
  void shell_copy(const char * src, const char * dst) {
    std::ifstream ifs(src, std::ios::in);
    std::string buffer;
    std::ofstream ofs(dst, std::ios::out);
    while (ifs.good()) {
      std::getline(ifs, buffer);
      if (!ifs.good())
        break;
      ofs << buffer << std::endl;
    }
    ifs.close();
    ofs.close();
  }

  // close all redirected file stream
  void close_all_stream() {
    fclose(stdin);
    fclose(stdout);
    fclose(stderr);
  }
  // Add color support
  // Reference: https://en.wikipedia.org/wiki/ANSI_escape_code#graphics
  // for color encoding.

#ifdef COLORED_OUTPUT
  std::string format_color_output(const std::string & line, const std::string & color) {
    return "\033[0;" + color + "m" + line + "\033[0m";
  }
  std::string format_bold_color_output(const std::string & line, const std::string & color) {
    return "\033[1;" + color + "m" + line + "\033[0m";
  }
#else
  std::string format_color_output(const std::string & line, const std::string & color) {
    return line;
  }
  std::string format_bold_color_output(const std::string & line, const std::string & color) {
    return line;
  }

#endif

}  // namespace Cshell
