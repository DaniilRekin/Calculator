#pragma once
#include <functional>
#include <unordered_map>
#include <cstring>
#include <string>
#include <string_view>
#include <charconv>
#include <optional>
#include <variant>
#include <vector>
#include <utility>
#include <stdexcept>
#include <numbers>
#include <cmath>
#include "Token.h"
#include "StaticIdentifiers.h"

class Lexer {
 private:
  std::optional<Token> TryToParseNumber(std::string_view& part) {
    double x = 0.0;
    auto res = std::from_chars(part.data(), part.data() + part.size(), x);
    if (res.ec != std::errc()) {
      return std::nullopt;
    }
    part.remove_prefix(static_cast<size_t>(res.ptr - part.data()));
    return Token{TokenType::Number, x};
  }

  std::optional<Token> TryToParseOperator(std::string_view& part) {
    OperatorType op_type = OperatorType::Undefined;
    switch (part.front()) {
      case '(': op_type = OperatorType::LeftBracket; break;
      case ')': op_type = OperatorType::RightBracket; break;
      case '+': op_type = OperatorType::Plus; break;
      case '-': op_type = OperatorType::Minus; break;
      case '*': op_type = OperatorType::Mult; break;
      case '/': op_type = OperatorType::Div; break;
      case '^': op_type = OperatorType::Pow; break;
      default:
        return std::nullopt;
    }

    part.remove_prefix(1);
    return Token{TokenType::Operator, op_type};
  }

  std::optional<Token> TryToParseConstant(std::string_view& part) {
    for (const auto& [c, _] : constants) {
      if (part.starts_with(c) &&
          (part.size() == c.size() || !std::isalnum(static_cast<unsigned char>(part[c.size()]))))
      {
          std::string_view value = part.substr(0, c.size());
          part.remove_prefix(c.size());
          return Token{TokenType::Constant, value};
      }
    }
    return std::nullopt;
}

  std::optional<Token> TryToParseFunction(std::string_view& part) {
    for (const auto& [f, _] : functions) {
      if (part.starts_with(f) &&
          (part.size() == f.size() || !std::isalnum(static_cast<unsigned char>(part[f.size()]))))
      {
        std::string_view value = part.substr(0, f.size());
        part.remove_prefix(f.size());
        return Token{TokenType::Function, value};
      }
    }
    return std::nullopt;
  }

 public:
  std::vector<Token> Tokenize(const std::string& input) {
    std::vector<Token> tokens;
    std::string_view part = input;
    while (part.size()) {
      if (std::isspace(static_cast<unsigned char>(part.front()))) {
        part.remove_prefix(1);
        continue;
      }

      std::optional<Token> token{Token{TokenType::Undefined, OperatorType::Undefined}};
      if (
        (token = TryToParseNumber(part)).has_value() ||
        (token = TryToParseOperator(part)).has_value() ||
        (token = TryToParseConstant(part)).has_value() ||
        (token = TryToParseFunction(part)).has_value()) {
          tokens.push_back(std::move(token.value()));
        } else {
          throw std::runtime_error("Undefined token");
        }
    }
    return tokens;
  }
};