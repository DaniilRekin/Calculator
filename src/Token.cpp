#include "../import/Token.h"

std::ostream& operator<<(std::ostream& os, OperatorType op) {
  switch (op) {
    case OperatorType::Plus:         return os << '+';
    case OperatorType::Minus:        return os << '-';
    case OperatorType::Mult:         return os << '*';
    case OperatorType::Div:          return os << '/';
    case OperatorType::Pow:          return os << '^';
    case OperatorType::LeftBracket:  return os << '(';
    case OperatorType::RightBracket: return os << ')';
    case OperatorType::Comma:        return os << ',';
    case OperatorType::Equal:        return os << '=';
    default:                         return os << '?';
  }
}

std::ostream& operator<<(std::ostream& os, const Token& token) {
  std::visit([&os](const auto& value) {
    os << value;
  }, token.val);

  return os;
}

std::ostream& operator<<(std::ostream& os, const std::vector<Token>& tokens) {
  os << "[\n ";

  for (size_t i = 0; i < tokens.size(); ++i) {
    if (i != 0)
      os << "\n ";

    os << tokens[i];
  }

  os << "\n]";
  return os;
}