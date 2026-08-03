#pragma once

#include <string>
#include <unordered_map>
#include <stdexcept>

class InputProcessor {
 public:
  enum class InputType { Command, Statement };
  InputType Analyze(const std::string& input);
};

enum class StatementType {
  ConstDeclaration,      // c = ...
  FunctionDeclaration,   // f(...) = ...
  ExpressionEvaluation,  // 2 + 5
  Undefined
};