#include "../include/History.hpp"

#include <iostream>

namespace Cshell {
  // @ AddHistory
  // Add current command line to the shell history
  // * Parameters
  // hls: current command line
  // cmd_id: command line id
  // * Returns
  // void
  void History::AddHistory(const std::string & his, long cmd_id) {
    size += 1;
    items.push_back(his);
    his_id.push_back(cmd_id);
  }

  // @ clear
  // clean history
  // * Returns
  // void
  void History::clear() {
    items.clear();
    his_id.clear();
    size = 0;
  }

  // @ GetSize
  // Get the current history length
  // * Returns
  // int: size of history length
  int History::GetSize() const { return (int)size; }

  // @ LoadHistory
  // Load history from history file
  // * Parameters
  // fname: history filename
  // * Returns
  // int: -1 if load failed; 0 if load succeeded.
  int History::LoadHistory(const char * fname) {
    std::ifstream ifs(fname, std::ios::in);
    if (ifs.fail()) {
      std::cerr << "Warning: " << fname << " not found." << std::endl;
      return -1;
    }
    std::string r_str;
    while (1) {
      std::getline(ifs, r_str);
      if (!ifs.good())
        break;
      std::pair<long, std::string> it = parse_history(r_str);
      if (it.first == -1) {
        std::cerr << "Aborting...." << std::endl;
        ifs.close();
        return -1;
      }
      AddHistory(it.second, it.first);
    }
    ifs.close();
    return 0;
  }

  // @ SaveHistory
  // Save history to history file
  // * Parameters
  // fname: history filename
  // * Returns
  // -1 if save failed, 0 if save succeeded.
  int History::SaveHistory(const char * fname) {
    std::ofstream ofs(fname, std::ios::out);
    if (ofs.fail())
      return -1;
    for (size_t i = 0; i < size; i++) {
      ofs << his_id[i] << " " << items[i] << std::endl;
    }
    ofs.close();
    return 0;
  }

// @ PrintHistory
// Print history log
// * Returns
// int: void
#define MAX_HIS_OUTPUT 100
  void History::PrintHistory() {
    if (size > MAX_HIS_OUTPUT) {
      for (size_t i = size - MAX_HIS_OUTPUT; i < size; i++) {
        std::cout << his_id[i] << '\t' << items[i] << std::endl;
      }
    }
    else {
      for (size_t i = 0; i < size; i++) {
        std::cout << his_id[i] << '\t' << items[i] << std::endl;
      }
    }
  }

  // @ get_cmd_number
  // get last command line number for history file loading
  // * Returns
  // long: last command line number
  long History::get_cmd_number() {
    if (size == 0)
      return -1;
    else
      return his_id[size - 1];
  }
}  // namespace Cshell
