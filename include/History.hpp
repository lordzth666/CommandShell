#ifndef CSHELL_HISTORY_HPP
#define CSHELL_HISTORY_HPP

#include <cstdio>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

#include "parse.hpp"

namespace Cshell {
  class History
  {
   private:
    std::vector<std::string> items;
    std::vector<long> his_id;
    size_t size;

   public:
    History() : size(0) {}
    // RO5
    History(const History & rhs) : items(rhs.items), his_id(rhs.his_id), size(rhs.size) {}
    History(History && rhs) noexcept {
      std::swap(items, rhs.items);
      std::swap(his_id, rhs.his_id);
      std::swap(size, rhs.size);
    }
    History & operator=(const History & rhs) {
      if (this != &rhs) {
        items = rhs.items;
        his_id = rhs.his_id;
        size = rhs.size;
      }
      return *this;
    }

    History & operator=(History && rhs) noexcept {
      if (this != &rhs) {
        std::swap(items, rhs.items);
        std::swap(his_id, rhs.his_id);
        std::swap(size, rhs.size);
      }
      return *this;
    }
    ~History() = default;
    // End of RO5

    int LoadHistory(const char * fname);
    void AddHistory(const std::string & his, long cmd_id);
    int SaveHistory(const char * fname);
    void clear();
    int GetSize() const;
    void PrintHistory();
    long get_cmd_number();
  };

#endif  //CSHELL_HISTORY_HPP
}
