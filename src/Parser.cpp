#include "../import/Parser.h"

double Parser::ParseAtom() {
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

  

        for (const auto& f : functions) {
          if (f.GetArity() == args.size() && f.GetName() == id) {
            return f.Evaluate(args);
          }
        }

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
      if (constants_.contains(id)) {
        return constants_.at(id);
      } else {
        for (const auto& c : constants) {
          if (c.name_ == id) {
            return c.Evaluate();
          }
        }
      }
      
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
