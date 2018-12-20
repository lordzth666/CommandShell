#ifndef CSHELL_ENVIROMENT_HPP
#define CSHELL_ENVIROMENT_HPP

#include <map>
#include <vector>

#include "parse.hpp"
#include "utilities.hpp"

namespace Cshell {
  class Environment
  {
   private:
    size_t size;
    std::vector<std::string> key;
    std::vector<std::string> value;
    std::vector<bool> cast;
    std::vector<std::pair<std::string, std::string> > alias;

   public:
    Environment();
    // RO5 begins
    Environment(const Environment & rhs) :
        size(rhs.size),
        key(rhs.key),
        value(rhs.value),
        cast(rhs.cast),
        alias(rhs.alias) {}
    Environment(Environment && rhs) noexcept {
      std::swap(size, rhs.size);
      std::swap(key, rhs.key);
      std::swap(value, rhs.value);
      std::swap(cast, rhs.cast);
      std::swap(alias, rhs.alias);
    }

    Environment & operator=(const Environment & rhs) {
      if (this != &rhs) {
        size = rhs.size;
        value = rhs.value;
        key = rhs.key;
        cast = rhs.cast;
        alias = rhs.alias;
      }
      return *this;
    }

    Environment & operator=(Environment && rhs) noexcept {
      if (this != &rhs) {
        std::swap(size, rhs.size);
        std::swap(key, rhs.key);
        std::swap(value, rhs.value);
        std::swap(cast, rhs.cast);
        std::swap(alias, rhs.alias);
      }

      return *this;
    }

    ~Environment() = default;

    // RO5 Ends
    int GetSize() const;
    void FetchEnv(const char * name);
    std::string GetEnv(const char * name) const;
    void PrintEnv(const char * name) const;
    void PrintEnv(const char * name, const std::string & color) const;
    void SetEnv(const char * name, const char * values);
    void SetEnv(const char * name, const std::string & value_str);
    std::string CheckEnvMisc(std::string r_str);
    void ExportAllEnv();
    void ExportEnv(const char * name);
    void Add_Alias(std::string line);
    std::string Find_Alias(std::string var);
  };
}  // namespace Cshell
#endif  //CSHELL_ENVIROMENT_HPP
