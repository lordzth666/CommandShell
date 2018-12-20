#include <cmath>
#include <iostream>

bool is_prime(long x) {
  if (x <= 1)
    return false;
  for (long j = 2; j <= sqrt(x); j++) {
    if (x % j == 0)
      return false;
  }
  return true;
}

int main() {
  while (1) {
    std::string istr;
    std::getline(std::cin, istr);
    if (!std::cin.good())
      break;
    long x = std::atoi(istr.c_str());
    if (is_prime(x))
      std::cout << x << std::endl;
  }
  return 0;
}
