#pragma once
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <vector>

#include "Exception.h"
#include "Identifiers.h"
#include "Token.h"

class Parser {
 private:
  size_t index;
  std::vector<Token> tokens;

  bool End() const { return index >= tokens.size(); }

  void Step() { index++; }

  const Token& Current() {
    if (End()) {
      throw Exception("Unexpected end of expression");
    }

    return tokens[index];
  }

 public:
  Parser() : index(0) {}

 public:
  // +, -
  double ParseAddition() {
    double value = ParseMultiplication();

    while (!End() && Current().IsOperator(OperatorType::Plus, OperatorType::Minus)) {
      OperatorType act = Current().GetOperatorType();
      Step();

      double right = ParseMultiplication();

      if (act == OperatorType::Plus) {
        value += right;
      } else {
        value -= right;
      }
    }

    return value;
  }

  // *, /
  double ParseMultiplication() {
    double value = ParseUnary();

    while (!End() && Current().IsOperator(OperatorType::Mult, OperatorType::Div)) {
      OperatorType act = Current().GetOperatorType();
      Step();

      double right = ParseUnary();

      if (act == OperatorType::Mult) {
        value *= right;
      } else {
        value /= right;
      }
    }

    return value;
  }

  // +x, -x
  // Важно: unary ниже степени
  double ParseUnary() {
    if (!End() && Current().IsOperator(OperatorType::Plus, OperatorType::Minus)) {
      OperatorType act = Current().GetOperatorType();
      Step();

      double value = ParseUnary();

      if (act == OperatorType::Minus) {
        return -value;
      }

      return value;
    }

    return ParsePower();
  }

  // ^
  double ParsePower() {
    double value = ParseAtom();
    if (!End() && Current().IsOperator(OperatorType::Pow)) {
      Step();
      double right = ParseUnary();
      value = std::pow(value, right);
    }
    return value;
  }

  // числа, константы, функции, скобки
  double ParseAtom() {
    // число
    if (Current().type == TokenType::Number) {
      double value = std::get<double>(Current().val);
      Step();
      return value;
    }

    // идентификатор:
    // pi, sin(), cos(), ...
    if (Current().type == TokenType::Identifier) {
      auto id = std::get<std::string_view>(Current().val);
      Step();

      // функция
      if (!End() && Current().IsOperator(OperatorType::LeftBracket)) {
        std::vector<double> args;

        Step();  // '('

        if (!Current().IsOperator(OperatorType::RightBracket)) {
          args.push_back(ParseAddition());

          while (!End() && Current().IsOperator(OperatorType::Comma)) {
            Step();

            args.push_back(ParseAddition());
          }

          if (!Current().IsOperator(OperatorType::RightBracket)) {
            throw Exception("Expected ')'");
          }
        }
        
        Step();

        if (args.size() == 0) {
          return f0.at(id)();
        }

        if (args.size() == 1) {
          return f1.at(id)(args[0]);
        }

        if (args.size() == 2) {
          return f2.at(id)(args[0], args[1]);
        }

        throw Exception("Wrong number of arguments");
      }

      // константа
      return constants.at(id);
    }

    // выражение в скобках
    if (Current().IsOperator(OperatorType::LeftBracket)) {
      Step();
      double value = ParseAddition();
      if (!Current().IsOperator(OperatorType::RightBracket)) {
        throw Exception("Expected ')'");
      }
      Step();
      return value;
    }
    throw Exception("Unexpected token");
  }

 public:
  double Parse(const std::vector<Token>& new_tokens) {
    index = 0;
    tokens = new_tokens;
    
    double value = ParseAddition();
    if (!End()) {
      throw Exception("Unexpected token after expression");
    }
    return value;
  }
};