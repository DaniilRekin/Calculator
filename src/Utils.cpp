#include "../import/Utils.h"

namespace ch {
bool isdigit(char ch) {
  return std::isdigit(static_cast<unsigned char>(ch));
}
bool isalpha(char ch) {
  return std::isalpha(static_cast<unsigned char>(ch));
}
bool isspace(char ch) {
  return std::isspace(static_cast<unsigned char>(ch));
}
bool isalnum(char ch) {
  return std::isalnum(static_cast<unsigned char>(ch));
}
bool is_identifier_first_char(char ch) {
  return std::isalpha(static_cast<unsigned char>(ch));
}
bool is_identifier_char(char ch) {
  return std::isalnum(static_cast<unsigned char>(ch)) || ch == '_';
}
}

std::string Format(double x, int n) {
  std::ostringstream out;
  out << std::fixed << std::setprecision(n) << x;
  std::string s = out.str();
  while (s.back() == '0') {
    s.pop_back();
  }
  if (s.back() == '.') {
    s.pop_back();
  }
  return s;
}