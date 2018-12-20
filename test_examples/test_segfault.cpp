#include <string.h>

#include <cstdlib>
#include <iostream>

int main() {
  char * s = (char *)"123214";
  s[0] = '3';
  std::cout << s;
  return 0;
}
