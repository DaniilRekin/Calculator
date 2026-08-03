#pragma once
#include <string_view>
#include <variant>
#include <vector>
#include <iostream>

enum class TokenType {
  Number,
  Operator,
  Identifier,
  Undefined,
};

enum class OperatorType {
  Plus,         // +
  Minus,        // -
  Mult,         // *
  Div,          // /
  Pow,          // ^
  LeftBracket,  // (
  RightBracket, // )
  Comma,        // ,
  Equal,        // =
  At,           // @
  Undefined
};

struct Token {
  TokenType type;
  std::variant<
    double,
    OperatorType, 
    std::string> val;

 public:
  
  bool operator==(const Token& other) const {
    return type == other.type && val == other.val;
  }

  OperatorType GetOperatorType() const {
    return std::get<OperatorType>(val);
  }

  template <class... Args>
  bool IsOperator(Args... args) const {
    return type == TokenType::Operator && ((args == std::get<OperatorType>(val)) || ...);
  }
};

std::ostream& operator<<(std::ostream& os, OperatorType op);
std::ostream& operator<<(std::ostream& os, const Token& token);
std::ostream& operator<<(std::ostream& os, const std::vector<Token>& tokens);