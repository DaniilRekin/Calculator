#include "../import/Analyzer.h"

std::ostream& operator<<(std::ostream& os, const Constant& obj) {
  os << "Name: " << obj.name_ << '\n';

  os << "Eval: [";
  for (size_t i = 0; i < obj.eval_.size(); ++i) {
    if (i > 0) os << ", ";
    os << obj.eval_[i];
  }
  os << "]";

  return os;
}

std::optional<double> Analyzer::Analyze(const std::vector<Token>& tokens) {
  Token equal{TokenType::Operator, OperatorType::Equal};

  // Есть оператор эквивалентность
  if (std::ranges::contains(tokens, equal)) {
    // Первый токен - это идентификатор сущности
    if (tokens[0].type == TokenType::Identifier) {
      auto id = std::get<std::string>(tokens[0].val);
      if (tokens[1].type == TokenType::Operator) {
        // Если является константой
        if (tokens[1].GetOperatorType() == OperatorType::Equal) {
          std::string name{id};
          std::vector<Token> eval{tokens.begin() + 2, tokens.end()};
          constants.push_back({name, eval});
          return std::nullopt;
        }
        // Если является функцией
        else if (tokens[1].GetOperatorType() == OperatorType::LeftBracket) {
          size_t pos = 2;
          std::vector<std::string> args;
          while (!tokens[pos].IsOperator(OperatorType::RightBracket)) {
            if (tokens[pos].type == TokenType::Identifier) {
              auto arg = std::get<std::string>(tokens[pos].val);
              args.emplace_back(arg);
            } else if (!tokens[pos].IsOperator(OperatorType::Comma)) {
              throw Exception("Некорректное определение параметров функции");
            }
            pos++;
            if (pos == tokens.size()) {
              throw Exception("Ожидается )");
            }
          }
          pos++;
          if (!tokens[pos].IsOperator(OperatorType::Equal)) {
            throw Exception("Ожидается =");
          }
          pos++;

          std::string name{id};
          std::vector<Token> eval{tokens.begin() + pos, tokens.end()};
          functions.push_back({name, args, eval});
          return std::nullopt;
        }
      }
    } else {
      throw Exception("Вычисляемое выражение не может содержать знак =");
    }

    throw Exception("Неизвестная ошибка");
  }

#pragma warning "Костыль"
  static Parser parser;
  return parser.Parse(tokens);
}