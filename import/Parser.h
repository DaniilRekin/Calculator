#pragma once
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <vector>

#include "Exception.h"
#include "Identifiers.h"
#include "Token.h"
#include "Constant.h"
#include "Function.h"
#include "Storage.h"

/*
  Парсер выполняющий вычисления
*/

class Parser {
 private:
  size_t index;
  std::vector<Token> tokens;

  double last = 0.0;

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
  double ParseAtom();

 public:
  double Parse(const std::vector<Token>& new_tokens) {
    index = 0;
    tokens = new_tokens;
    
    double value = ParseAddition();
    if (!End()) {
      throw Exception("Unexpected token after expression");
    }
    return last = value;
  }
};