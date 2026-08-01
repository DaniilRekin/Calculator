#pragma once
#include <string_view>
#include <variant>

enum class TokenType {
  Number,
  Operator,
  Constant,
  Function,
  Undefined
};

enum class OperatorType {
  Plus,
  Minus,
  Mult,
  Div,
  Pow,
  LeftBracket,
  RightBracket,
  Undefined
};

struct Token {
  TokenType type;
  std::variant<
    double,
    OperatorType, 
    std::string_view> val;
};