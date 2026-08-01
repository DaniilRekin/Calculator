#pragma once
#include <vector>
#include <stdexcept>
#include <cmath>
#include <iostream>
#include "Token.h"
#include "StaticIdentifiers.h"

class Parser {
 private:
  size_t pos = 0;
  std::vector<Token> token;

  // +, -
  double Level1() {
    double value = Level2();
    OperatorType op = OperatorType::Undefined;
    if (pos < token.size()) {
    while (
      op = std::get<OperatorType>(token[pos].val),
      token[pos].type == TokenType::Operator && (
        op == OperatorType::Plus || op == OperatorType::Minus
      )) {
        pos++;
        double right = Level2();
        value = (op == OperatorType::Plus? value + right : value - right);
        if (pos >= token.size()) {
          break;
        }
      }
    }
    return value;
  }

  // *, /
  double Level2() {
    double value = Level3();
    OperatorType op = OperatorType::Undefined;
    if (pos < token.size()) {
      while (
      op = std::get<OperatorType>(token[pos].val),
      token[pos].type == TokenType::Operator && (
        op == OperatorType::Mult || op == OperatorType::Div
      )) {
        pos++;
        double right = Level3();
        value = (op == OperatorType::Mult? value * right : value / right);
        if (pos >= token.size()) {
          break;
        }
      }
    }
    return value;
  }

  // ^
  double Level3() {
    double value = Level4();
    if (token[pos].type == TokenType::Operator && std::get<OperatorType>(token[pos].val) == OperatorType::Pow) {
      pos++;
      value = std::pow(value, Level3());
    }
    return value;
  }

  // f(), (), 1.0
  double Level4() {
    const Token& current = token[pos];

    // Численный литерал
    if (current.type == TokenType::Number) {
      pos++;
      return std::get<double>(current.val);
    }

    // Константа
    if (current.type == TokenType::Constant) {
      pos++;
      auto const_name = std::get<std::string_view>(current.val);
      if (constants.contains(const_name)) {
        return constants.at(const_name)();
      }
      throw std::runtime_error("Неизвестная константа");
    }

    // Вызов функции
    if (current.type == TokenType::Function) {
      pos++;
      if (token[pos].type != TokenType::Operator || std::get<OperatorType>(token[pos].val) != OperatorType::LeftBracket) {
        throw std::runtime_error("Ожидается '('");
      }
      pos++;
      double value = Level1();
      if (token[pos].type != TokenType::Operator || std::get<OperatorType>(token[pos].val) != OperatorType::RightBracket) {
        throw std::runtime_error("Ожидается ')'");
      }
      pos++;

      auto func_name = std::get<std::string_view>(current.val);
      if (functions.contains(func_name)) {
        return functions.at(func_name)(value);
      }
      throw std::runtime_error("Неизвестная функция");
    }

    // Скобки
    if (token[pos].type == TokenType::Operator && std::get<OperatorType>(token[pos].val) == OperatorType::LeftBracket) {
      pos++;
      double value = Level1();
      if (token[pos].type != TokenType::Operator || std::get<OperatorType>(token[pos].val) != OperatorType::RightBracket) {
        throw std::runtime_error("Ожидается ')'");
      }
      pos++;
      return value;
    }
  }

 public:
  double Parse(const std::vector<Token>& tokens) {
    pos = 0;
    this->token = tokens;
    return Level1();
  }
};