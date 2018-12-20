#ifndef CSHELL_CSHELL_HPP
#define CSHELL_CSHELL_HPP

#include <iostream>
#include <string>
#include <vector>


#include "Environment.hpp"
#include "History.hpp"
#include "defs.hpp"
#include "file.hpp"
#include "parse.hpp"
#include "utilities.hpp"
#include "version.hpp"
#include "Config.hpp"

namespace Cshell {
  class Cshell
  {
   private:
    History history;
    Environment env;
    Config cfg;
    long cmd_cnt;

   public:
    Cshell() : cmd_cnt(0) {
      cfg._setProjectRoot(".");
      run_from_file(cfg.cshrc_path.c_str());
      // Now fixed this path
      std::string fixed_path;
      run_one_line("pwd >initialPath.txt");
      std::ifstream ifs("initialPath.txt", std::ios::in);
      std::getline(ifs, fixed_path);
      cfg._setProjectRoot(fixed_path);
      ifs.close();
    }
    
    // RO5
    Cshell(const Cshell & rhs) {
      history = rhs.history;
      env = rhs.env;
      cmd_cnt = rhs.cmd_cnt;
    }

    Cshell(Cshell && rhs) noexcept {
      std::swap(history, rhs.history);
      std::swap(env, rhs.env);
      std::swap(cmd_cnt, rhs.cmd_cnt);
    }

    Cshell & operator=(const Cshell & rhs) {
      if (this != &rhs) {
        history = rhs.history;
        env = rhs.env;
        cmd_cnt = rhs.cmd_cnt;
      }
      return *this;
    }

    Cshell & operator=(Cshell && rhs) noexcept {
      if (this != &rhs) {
        std::swap(history, rhs.history);
        std::swap(env, rhs.env);
        std::swap(cmd_cnt, rhs.cmd_cnt);
      }
      return *this;
    }

    ~Cshell() = default;
    // End of RO5
    void start();
    int run_once(const char * filename, std::vector<std::string> argv, const char ** argenv);
    int run_from_file(const char * filename);
    int run_one_line(std::string line);
    int run_one_line_with_pipe(std::string line);
    int run();
    void Printprompt();
    void quit();
    int MiscHandler(std::string cmd_name, int argc, std::vector<std::string> argv);
    // File handler
    void change_dir(const std::string & arg);
    int run_process(const char * filename,
                    const std::vector<std::string> & argv,
                    const char ** argenv);
  };
}  // namespace Cshell
#endif  //CSHELL_CSHELL_H
