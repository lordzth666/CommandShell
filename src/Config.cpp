//
// Created by lordzth on 12/20/18.
//

#include "../include/Config.hpp"

namespace Cshell {

    Config::Config(): use_path("PATH"){

    }

    Config::Config(const std::string &project_root) {
        _setProjectRoot(project_root);
    }

    void Config::_setProjectRoot(const std::string &project_root) {
        project_path = project_root;
        pipe_out_file = project_path + "/tmp/pipeoutlog0xi2f.pipetmp.ubuntu18.out";
        pipe_in_file = project_path + "/tmp/pipeinlog0xi2f.pipetmp.ubuntu18.in";
        pipe_in_cmd = "<" + pipe_in_file;
        pipe_out_cmd = ">" + pipe_out_file;
        cd_tmp_file = project_root + "/tmp/cdtmplog0xi2f.cdtmp.ubuntu18";
        cd_tmp_cmd = ">" +  cd_tmp_file;
        history_path = project_root + "/.csh_history";
        cshrc_path = project_root + "/.cshrc";
    }

    void Config::flushProjectRoot(const std::string &project_root) {
        std::cerr << "Warning: flushing project root directory may lead to unstability of the shell." << std::endl;
        _setProjectRoot(project_root);
    }
}
