#include "../include/Cshell.hpp"

namespace Cshell {
  // @ start
  // Start cshell and load history and cshrc
  // *Returns
  // void
  void Cshell::start() {
    std::cout << "Welcome to Cshell " << VERSION << " on " << SYS_VER << std::endl;
    std::cout << "[GCC 7.3.0] on linux2" << std::endl;
    std::cout << "Released (Dec 5 2018, 23:59:59)" << std::endl;
    history.LoadHistory(cfg.history_path.c_str());
    cmd_cnt = history.get_cmd_number() + 1;
  }

  // @ run_once
  // Run a parsed command once with fork()
  // * Parameters
  // filename: command name
  // argv: command argv
  // argenv: command environment argv
  // * Returns
  // int: 0 if exit success.
  int Cshell::run_once(const char * filename, std::vector<std::string> argv, const char ** argenv) {
    pid_t cpid;
    cpid = fork();
    if (cpid == -1) {
      perror("Fork error! Cannot create a new process\n");
    }
    if (cpid == 0) {
      int status = run_process(filename, argv, argenv);
      _exit(status);
    }
    else {
      wait_process(cpid);
    }
    return 0;
  }

  // @ run_process
  // execute the commmand in the new process
  // * Parameters
  // filename: command name
  // argv: command argv
  // argenv: command environment argv
  // * Returns
  // int: program exit code
  int Cshell::run_process(const char * filename,
                          const std::vector<std::string> & argv,
                          const char ** argenv) {
    //std::string path_string = env.GetEnv("PATH");
    std::string path_string = env.GetEnv(cfg.use_path.c_str());
    std::vector<std::string> path_vector = unpack_path(path_string);
    path_vector.emplace_back("");
    size_t pv_size = path_vector.size();
    int status = -1;
    int argc = 0;
    char ** argv_ch = remove_redirect(argv, &argc);
    if (argv_ch == nullptr)
      return SHTERMINATE;
    // iterate all path
    std::vector<std::string> path_str_vector = embed_path_and_filename(path_vector, filename);
    for (size_t i = 0; i < pv_size; i++) {
      const char * new_filename = path_str_vector[i].c_str();
      status = execve((char *)new_filename, argv_ch, (char **)argenv);
      if (status != -1) {
        break;
      }
    }
    path_vector.pop_back();
    // remove the redundant ""
    if (status == -1) {
      std::cerr << filename << ": command not found." << std::endl;
      for (int i = 0; i < argc; i++)
        free(argv_ch[i]);
      free(argv_ch);
      close_all_stream();
      return status;
    }
    for (int i = 0; i < argc; i++)
      free(argv_ch[i]);
    free(argv_ch);
    close_all_stream();
    return status;
  }

  // @ run_one_line
  // Run one raw command line without pipe
  // * Parameters
  // line: comamnd line
  // * Returns
  // int: shell exit code (see $PROJECT_ROOT/include/defs.hpp)
  int Cshell::run_one_line(std::string line) {
    std::set<size_t> sp_c;
    line = parse_comment(line);
    if (line == "") {
      return SHNORMAL;
    }
    if (format_string(line) != 1) {
      std::cerr << "Bad format!" << std::endl;
      std::cerr << line << std::endl;
      return SHNORMAL;
    }
    char ** argenv = (char **)malloc(sizeof(char *) * 1);
    argenv[0] = nullptr;
    // get special char positions(escape characters)
    line = parse_special_char(line, sp_c);
    int argc;
    std::vector<bool> cast;
    // get the argvs & determine whether a non-escape to escape interpretation is needed
    std::vector<std::string> argv = parse_command(line, sp_c, cast, &argc);
    for (size_t i = 0; i < argv.size(); i++) {
      if (!cast[i]) {
        // parse the environment variables & escape characters
        argv[i] = env.CheckEnvMisc(argv[i]);
      }
    }
    // Check if a special operation is needed
    int c_status = MiscHandler(argv[0], argc, argv);
    // Early stopping
    if (c_status == SHSKIP) {
      free(argenv[0]);
      free(argenv);
      return SHSKIP;
    }
    else if (c_status == SHTERMINATE) {
      free(argenv[0]);
      free(argenv);
      return SHTERMINATE;
    }
    // run as a normal command
    const char * filename = argv[0].c_str();
    int sh_status = run_once(filename, argv, (const char **)argenv);
    free(argenv[0]);
    free(argenv);
    return sh_status;
  }

  // @ run
  // Start running an interactive shell
  // * Returns
  // int: exit status
  int Cshell::run() {
    std::string line;
    std::string run_line;
    int r_status = 0;
    start();
    while (true) {
#ifndef NOLIMIT
      if (cmd_cnt > MAX_CMD)
        break;
#endif
      Printprompt();
      line = "";
      run_line = "";
      // parsing incomplete commands
      bool first_input = true;
      do {
        if (!first_input)
          std::cout << "<";
        std::getline(std::cin, line);
        if (!std::cin.good()) {
          break;
        }
        run_line += line;
        if (!check_complete(run_line)) {
          first_input = false;
        }
        else {
          break;
        }
      } while (1);
      if (!std::cin.good()) {
        quit();
        break;
      }
      if (check_empty(run_line))
        continue;
      // Add history
      history.AddHistory(run_line, cmd_cnt);
      cmd_cnt += 1;
      // detect whether it is a piped command
      if (!has_pipe(run_line)) {
        r_status = run_one_line(run_line);
        if (r_status == SHTERMINATE)
          break;
      }
      else {
        r_status = run_one_line_with_pipe(run_line);
        if (r_status == SHTERMINATE)
          break;
      }
    }
    return r_status;
  }

  // @ run_from_file
  // Start running shell from a shell script file
  // * Parameters
  // filename: script filename
  // * Returns
  // int: shell exit code
  int Cshell::run_from_file(const char * filename) {
    std::ifstream ifs(filename, std::ios::in);
    // Check failure
    if (ifs.fail()) {
      std::cout << filename << ": file not found." << std::endl;
      return SHTERMINATE;
    }
    std::string line;
    std::string run_line;
    int r_status = 0;
    while (1) {
      line = "";
      run_line = "";
      do {
        std::getline(ifs, line);
        if (!ifs.good()) {
          break;
        }
        run_line += line;
        // incomplete command check
        if (!check_complete(run_line)) {
          continue;
        }
        else {
          break;
        }
      } while (1);
      if (!ifs.good()) {
        break;
      }
      if (check_empty(run_line))
        continue;
      // Check if command has pipe

      if (!has_pipe(run_line)) {
        r_status = run_one_line(run_line);
        if (r_status == SHTERMINATE)
          break;
      }
      else {
        r_status = run_one_line_with_pipe(run_line);
        if (r_status == SHTERMINATE)
          break;
      }
    }
    ifs.close();
    return r_status;
  }

  // @ run_one_line_with_pipe
  // Unravel and run a piped command line
  // * Parameters
  // line: piped command line
  // * Returns
  // int: shell exit code
  int Cshell::run_one_line_with_pipe(std::string line) {
    std::vector<std::string> commands = split_piped_command(line);
    size_t command_cnt = commands.size();
    // starting a series of piped command
    for (size_t i = 0; i < command_cnt; i++) {
      std::string command_i = commands[i];
      int r_status;
      // start
      if (i == 0) {
        command_i += " ";
        command_i += cfg.pipe_out_cmd;
        r_status = run_one_line(command_i);
        if (r_status == SHTERMINATE)
          return SHTERMINATE;
      }
      // finalized
      else if (i == command_cnt - 1) {
        command_i += " ";
        command_i += cfg.pipe_in_cmd;
        shell_copy(cfg.pipe_out_file.c_str(), cfg.pipe_in_file.c_str());
        r_status = run_one_line(command_i);
        if (r_status == SHTERMINATE)
          return SHTERMINATE;
      }
      // normal
      else {
        command_i += " ";
        command_i += cfg.pipe_in_cmd;
        command_i += " ";
        command_i += cfg.pipe_out_cmd;
        shell_copy(cfg.pipe_out_file.c_str(), cfg.pipe_in_file.c_str());
        r_status = run_one_line(command_i);
        if (r_status == SHTERMINATE)
          return SHTERMINATE;
      }
    }
    // clean
    std::string rm_cmd;
    rm_cmd += "rm -rf ";
    rm_cmd += cfg.pipe_out_file;
    rm_cmd += " ";
    rm_cmd += cfg.pipe_in_file;
    run_one_line(rm_cmd);
    return 0;
  }

  // @ MiscHandler
  // Handle special corner cases without running
  // * Parameters
  // cmd: command filename
  // argv: command argv
  // * Returns
  // int: shell exit code
  int Cshell::MiscHandler(std::string cmd_name, int argc, std::vector<std::string> argv) {
    std::string alias_cmd = env.Find_Alias(cmd_name);
    // no command
    if (!alias_cmd.empty()) {
      for (size_t i = 1; i < argv.size(); i++)
        alias_cmd = alias_cmd + " " + argv[i];
      run_one_line(alias_cmd);
      return SHSKIP;
    }

    // exit command
    if (cmd_name == "exit") {
      quit();
      return SHTERMINATE;
    }

    // add color to echo
    if (cmd_name == "echo") {
      if (argc == 1)
        return SHNORMAL;
      // small patch, for this symbol is used for redirection.
      if ((argv[1] == "\">\"") || (argv[1] == "\'>\'") || (argv[1] == ">")) {
        std::cout << ">" << std::endl;
        return SHSKIP;
      }
      if ((argv[1] == "\"<\"") || (argv[1] == "\'<\'") || (argv[1] == "<")) {
        std::cout << "<" << std::endl;
        return SHSKIP;
      }
      if ((argv[1] == "\">>\"") || (argv[1] == "\'>>\'") || (argv[1] == ">>")) {
        std::cout << ">>" << std::endl;
        return SHSKIP;
      }

      if (argv[1].size() < 7) {
        return SHNORMAL;
      }

      // Add flashy things
      if (argv[1].substr(0, 6) == "[Info]") {
        for (size_t i = 1; i < argv.size(); i++) {
          std::cout << format_color_output(argv[i], GREEN);
          if (i != argv.size())
            std::cout << " ";
        }
        std::cout << std::endl;
        return SHSKIP;
      }

      if (argv[1].substr(0, 5) == "[Test") {
        for (size_t i = 1; i < argv.size(); i++) {
          std::cout << format_bold_color_output(argv[i], MAGENTA);
          if (i != argv.size())
            std::cout << " ";
        }
        std::cout << std::endl;
        return SHSKIP;
      }

      if (argv[1].substr(0, 7) == "THZHANG") {
        for (size_t i = 1; i < argv.size(); i++) {
          std::cout << format_bold_color_output(argv[i], BLUE);
          if (i != argv.size())
            std::cout << " ";
        }
        std::cout << std::endl;
        return SHSKIP;
      }

      return SHNORMAL;
    }

    // cd command
    if (cmd_name == "cd") {
      if (argc == 1) {
        change_dir(env.GetEnv("HOME"));
        return SHSKIP;
      }
      if (argc > 2) {
        std::cerr << "bash: cd: too many arguments." << std::endl;
        return SHSKIP;
      }
      change_dir(argv[1]);
      return SHSKIP;
    }

    // history command
    if (cmd_name == "history") {
      if (argc == 1) {
        history.PrintHistory();
        return SHSKIP;
      }
      else {
        if (argv[1] == "-c")
          history.clear();
        return SHSKIP;
      }
    }

    // export command
    if (cmd_name == "export") {
      if (argc == 1)
        env.ExportAllEnv();
      else {
        for (int i = 1; i < argc; i++)
          env.ExportEnv(argv[i].c_str());
      }
      return SHSKIP;
    }

    // set command
    if (cmd_name == "set") {
      if (argc <= 1) {
        return SHSKIP;
      }
      if (!builtin::is_valid_varname(argv[1])) {
        std::cerr << "Error! Invalid variable name " << argv[1] << std::endl;
        return SHSKIP;
      }
      std::string value_str;
      for (int i = 2; i < argc; i++) {
        std::string tmp(argv[i]);
        if (i != argc - 1)
          value_str += tmp + " ";
        else
          value_str += tmp;
      }
      env.SetEnv(argv[1].c_str(), value_str.c_str());
      return SHSKIP;
    }

    // inc command
    if (cmd_name == "inc") {
      if (argc <= 1) {
        std::cerr << "Cshell: inc: missing operands." << std::endl;
        return SHSKIP;
      }
      if (!builtin::is_valid_varname(argv[1])) {
        std::cerr << "Error! Invalid variable name " << argv[1] << std::endl;
        return SHSKIP;
      }
      long s_int = builtin::to_int(env.GetEnv(argv[1].c_str())) + 1;
      std::string up_str = std::to_string(s_int);
      env.SetEnv(argv[1].c_str(), up_str.c_str());
      return SHSKIP;
    }

    // run: run specific command shell file
    // source: source specific command shell file
    if ((cmd_name == "run") || (cmd_name == "source")) {
      if (argc <= 1) {
        std::cerr << "Cshell: " << cmd_name << ": missing filename. run [filename]" << std::endl;
        return SHSKIP;
      }
      run_from_file(argv[1].c_str());
      return SHSKIP;
    }

    // alias: making shell more conveninent
    if (cmd_name == "alias") {
      std::string alias_str = "";
      for (size_t i = 1; i < argv.size(); i++)
        alias_str += argv[i] + " ";
      env.Add_Alias(alias_str);
      return SHSKIP;
    }
    return SHNORMAL;
  }

  // @ change_dir
  // 'cd' command for change directory
  // * Parameters
  // arg: input cd command
  // * Returns
  // void
  void Cshell::change_dir(const std::string & arg) {
    const char * name = arg.c_str();
    if (chdir(name) == 0) {
      std::string cmd = "";
      cmd += "pwd ";
      cmd += cfg.cd_tmp_cmd;
      run_one_line(cmd);
      // fetch pwd after change
      std::ifstream ifs(cfg.cd_tmp_file, std::ios::in);
      std::string cur_env_path;
      std::getline(ifs, cur_env_path);
      ifs.close();
      env.SetEnv("PWD", cur_env_path.c_str());
      // cleaning temporary files
      cmd = "rm -rf ";
      cmd += cfg.cd_tmp_file;
      run_one_line(cmd);
    }
    else {
      std::cerr << "Cshell: cd: " << arg << ": no such file or directory." << std::endl;
    }
  }

  // @ Printpromt
  // Print the prompt characters
  // * Returns
  // void
  void Cshell::Printprompt() {
    env.PrintEnv("USER", GREEN);
    std::cout << "@";
    env.PrintEnv("DESKTOP_SESSION", MAGENTA);
    std::cout << ":";
    env.PrintEnv("PWD", BLUE);
    std::cout << format_color_output("$ ", YELLOW);
  }

  // @ quit()
  // Quit the shell.
  // * Returns
  // void
  void Cshell::quit() {
    std::cout << "Exiting ..." << std::endl;
    history.SaveHistory(cfg.history_path.c_str());
  }
}  // namespace Cshell
