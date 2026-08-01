#pragma once
#include <string_view>
#include <variant>

enum class TokenType {
  Number,
  Operator,
  Identifier,
  Undefined,

  Constant [[deprecated("Use Identifier")]] = Identifier,
  Function [[deprecated("Use Identifier")]] = Identifier
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
  Undefined
};

struct Token {
  TokenType type;
  std::variant<
    double,
    OperatorType, 
    std::string_view> val;

 public:
  
  OperatorType GetOperatorType() const {
    return std::get<OperatorType>(val);
  }

  template <class... Args>
  bool IsOperator(Args... args) const {
    return type == TokenType::Operator && ((args == std::get<OperatorType>(val)) || ...);
  }
};