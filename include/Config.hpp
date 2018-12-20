//
// Created by lordzth on 12/20/18.
//

#ifndef CSHELL_CONFIG_HPP
#define CSHELL_CONFIG_HPP

#include <string>

#include <iostream>

namespace Cshell {
    class Config {

    public:
        std::string project_path;
        std::string pipe_out_file;
        std::string pipe_in_file;
        std::string cd_tmp_file;
        std::string pipe_in_cmd;
        std::string pipe_out_cmd;
        std::string cd_tmp_cmd;
        std::string history_path;
        std::string cshrc_path;

        std::string use_path;

    public:

        Config();

        explicit Config(const std::string & project_root);

        void _setProjectRoot(const std::string & project_root);

        void flushProjectRoot(const std::string & project_root);

        ~Config() = default;
    };
}



#endif //CSHELL_CONFIG_HPP
