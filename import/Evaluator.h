#pragma once
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <format>
#include <vector>

#include "Context.h"
#include "Constant.h"
#include "Exception.h"
#include "Function.h"
#include "Identifiers.h"
#include "Token.h"


class GlobalContext;
class LocalContext;

class Evaluator {
 private:
  size_t index;
  std::vector<Token> tokens;
  GlobalContext* global_context_;
  LocalContext* local_context_;

 private:
  bool End() const;
  void Step();
  const Token& Current();

 public:
  Evaluator() : index(0) {}

 public:
  // +, -
  double ParseAddition();

  // *, /
  double ParseMultiplication();

  // +x, -x
  // Важно: unary ниже степени
  double ParseUnary();

  // ^
  double ParsePower();

  // 2.0, C, f(), @last, $value, ()
  double ParseAtom();

 public:
  double Parse(
    const std::vector<Token>& new_tokens, GlobalContext* global, LocalContext* local
  );
};