#include "../import/Evaluator.h"
#include <cassert>

bool Evaluator::End() const {
  return index >= tokens.size();
}

void Evaluator::Step() {
  index++;
}

const Token& Evaluator::Current() {
  if (End()) {
    throw Exception("Unexpected end of expression");
  }
  return tokens[index];
}

// +, -
double Evaluator::ParseAddition() {
  double value = ParseMultiplication();

  while (!End() && Current().OperatorMatches(OperatorType::Plus, OperatorType::Minus)) {
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
double Evaluator::ParseMultiplication() {
  double value = ParseUnary();

  while (!End() && Current().OperatorMatches(OperatorType::Mult, OperatorType::Div)) {
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
double Evaluator::ParseUnary() {
  if (!End() && Current().OperatorMatches(OperatorType::Plus, OperatorType::Minus)) {
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
double Evaluator::ParsePower() {
  double value = ParseAtom();
  if (!End() && Current().OperatorMatches(OperatorType::Pow)) {
    Step();
    double right = ParseUnary();
    value = std::pow(value, right);
  }
  return value;
}

// 2.0, C, f(), @last, $value, ()
double Evaluator::ParseAtom() {
  // число
  if (Current().type == TokenType::Number) {
    double value = std::get<double>(Current().val);
    Step();
    return value;
  }

  // идентификатор @last
  if (Current().OperatorMatches(OperatorType::At)) {
    Step();
    if (Current().type == TokenType::Identifier) {
      const std::string& property = Current().GetString();
      if (local_context_) {
        Step();
        return local_context_->GetProperty(property);
      } else {
        Step();
        return global_context_->GetProperty(property);
      }
    }
    throw Exception("Некорректный идентификатор @");
  }

  // идентификатор $value
  if (Current().OperatorMatches(OperatorType::Dollar)) {
    Step();
    if (Current().type == TokenType::Identifier) {
      const std::string& variable = Current().GetString();
      Step();
      return global_context_->GetVariable(variable);
      
    }
    throw Exception("Некорректный идентификатор $");
  }

  // идентификатор:
  // pi, sin(), cos(), ...
  if (Current().type == TokenType::Identifier) {
    auto id = std::get<std::string>(Current().val);
    Step();

    // функция
    if (!End() && Current().OperatorMatches(OperatorType::LeftBracket)) {
      // Вызов функции
      std::vector<double> args;
      Step();  // '('
      if (!Current().OperatorMatches(OperatorType::RightBracket)) {
        args.push_back(ParseAddition());
        while (!End() && Current().OperatorMatches(OperatorType::Comma)) {
          Step();
          args.push_back(ParseAddition());
        }
        if (!Current().OperatorMatches(OperatorType::RightBracket)) {
          throw Exception("Expected ')'");
        }
      }

      Step();  // ')'
      return global_context_->ExecuteFunction(id, args);

      throw Exception("Wrong number of arguments");
    }

    // константа
    return global_context_->GetConstant(id);
  }

  // выражение в скобках
  if (Current().OperatorMatches(OperatorType::LeftBracket)) {
    Step();
    double value = ParseAddition();
    if (!Current().OperatorMatches(OperatorType::RightBracket)) {
      throw Exception("Expected ')'");
    }
    Step();
    return value;
  }

  throw Exception("Unexpected token");
}

double Evaluator::Parse(
  const std::vector<Token>& new_tokens, GlobalContext* global, LocalContext* local
) {
  index = 0;
  tokens = new_tokens;
  global_context_ = global;
  local_context_ = local;

  double value = ParseAddition();

  if (!End()) {
    throw Exception("Unexpected token after expression");
  }
  return value;
}
