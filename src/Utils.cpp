#include "../import/Utils.h"

bool IsDigit(char ch) {
  return std::isdigit(static_cast<unsigned char>(ch));
}

bool IsAlpha(char ch) {
  return std::isalpha(static_cast<unsigned char>(ch));
}

bool IsSpace(char ch) {
  return std::isspace(static_cast<unsigned char>(ch));
}

bool IsIdentifierChar(char ch) {
  auto uch = static_cast<unsigned char>(ch);
  return std::isalnum(uch) || uch == '_';
}