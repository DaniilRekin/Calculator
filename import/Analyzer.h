#pragma once
#include <vector>
#include <algorithm>
#include <ranges>
#include <ostream>
#include "Constant.h"
#include "Function.h"
#include "Token.h"
#include "Exception.h"
#include "Parser.h"
#include "Storage.h"

class Analyzer {
 public:
  enum Type {
    ConstDeclaration,      // c = ...
    FunctionDeclaration,   // f(...) = ...
    ExpressionEvaluation,  // 2 + 5
  };

 public:
  std::optional<double> Analyze(const std::vector<Token>& tokens);
};