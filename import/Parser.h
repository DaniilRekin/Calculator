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
#include "Context.h"
#include "Evaluator.h"

class Parser {
 public:
  enum class Type {
    // Объявление сущности (константа / функция)
    ConstDeclaration,      // C = ...
    FunctionDeclaration,   // f(...) = ...

    // Присвоение значения (переменная / свойство)
    VariableAssignment,    // $count = 0.0
    PropertyAssignment,    // f(x, y):@last = 0.0
                           // @last = 0.0

    // Удаление константы, функции, переменной
    DeleteConstVarFunc,    // ~C
                           // ~f(x, y)
                           // ~$count
    
    // Вычисляемое выражение
    ExpressionEvaluation,  // 2 + 5
  };

  struct ParseResult {
    Type type;
    std::optional<double> value;
  };

 public:
  ParseResult Parse(const std::vector<Token>& tokens, GlobalContext* context);
};