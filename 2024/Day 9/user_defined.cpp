#include "user_defined.h"
namespace user_defined {
std::vector<std::string> split(std::string s,
                                             std::string delimiter) {
  std::vector<std::string> v;
  size_t pos = 0;
  std::string token;
  while ((pos = s.find(delimiter)) != std::string::npos) {
    token = s.substr(0, pos);
    if (!token.empty()) {
      v.push_back(token);
    }
    s.erase(0, pos + delimiter.length());
  }
  v.push_back(s);
  return v;
}

std::vector<int> split_int(std::string s, std::string delimiter) {
  std::vector<int> v;
  size_t pos = 0;
  std::string token;
  while ((pos = s.find(delimiter)) != std::string::npos) {
    token = s.substr(0, pos);
    if (!token.empty()) {
      v.push_back(std::stoi(token));
    }
    s.erase(0, pos + delimiter.length());
  }
  v.push_back(std::stoi(s));
  return v;
}

} // namespace user_defined
