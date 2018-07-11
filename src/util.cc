#include "util.h"
#include <string>

struct iequal {
  bool operator()(int c1, int c2) const {
    return std::toupper(c1) == std::toupper(c2);
  }
};

bool iequals(const std::string& str1, const std::string& str2) {
  return std::equal(str1.begin(), str1.end(), str2.begin(), iequal());
}
