#include "../import/Token.h"

bool Token::IsNumber() const {
  return type == TokenType::Number;
}

bool Token::IsOperator() const {
  return type == TokenType::Operator;
}

bool Token::IsIdentifier() const {
  return type == TokenType::Identifier;
}

double Token::GetDouble() const {
  return std::get<double>(val);
}

OperatorType Token::GetOperatorType() const {
  return std::get<OperatorType>(val);
}

const std::string& Token::GetString() const {
  return std::get<std::string>(val);
}

OperatorType Token::CharToOperatorType(char ch) {
  switch (ch) {
    case '+': return OperatorType::Plus;
    case '-': return OperatorType::Minus;
    case '*': return OperatorType::Mult;
    case '/': return OperatorType::Div;
    case '^': return OperatorType::Pow;
    case '(': return OperatorType::LeftBracket;
    case ')': return OperatorType::RightBracket;
    case ',': return OperatorType::Comma;
    case '=': return OperatorType::Equal;
    case '@': return OperatorType::At;
    case ':': return OperatorType::Colon;
    case '$': return OperatorType::Dollar;
    case '~': return OperatorType::Tilde;
    default: throw std::runtime_error("");
  }
}

char Token::OperatorTypeToChar(OperatorType op) {
  switch (op) {
    case OperatorType::Plus: return '+';
    case OperatorType::Minus: return '-';
    case OperatorType::Mult: return '*';
    case OperatorType::Div: return '/';
    case OperatorType::Pow: return '^';
    case OperatorType::LeftBracket: return '(';
    case OperatorType::RightBracket: return ')';
    case OperatorType::Comma: return ',';
    case OperatorType::Equal: return '=';
    case OperatorType::At: return '@';
    case OperatorType::Colon: return ':';
    case OperatorType::Dollar: return '$';
    case OperatorType::Tilde: return '~';
    default: throw std::exception();
  }
}

std::ostream& operator<<(std::ostream& os, OperatorType op) {
  std::cout << static_cast<char>(op);
}

std::ostream& operator<<(std::ostream& os, const Token& token) {
  std::visit([&os](const auto& value) { os << value; }, token.val);
  return os;
}

std::ostream& operator<<(std::ostream& os, const std::vector<Token>& tokens) {
  // os << "[\n ";
  for (size_t i = 0; i < tokens.size(); ++i) {
    if (i != 0) os << "\t";
    os << tokens[i];
  }
  //os << "\n]";
  return os;
}