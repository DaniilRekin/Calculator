#include <span>
#include <utility>
#include "../import/Parser.h"

std::pair<std::vector<std::string>, size_t> GetFuncArgs(std::span<const Token> tokens) {
  size_t position = 0;
  size_t comma_count = 0;
  std::vector<std::string> args;
  // x, y, z
  while (position < tokens.size() &&
         !tokens[position].OperatorMatches(OperatorType::RightBracket)) {
    if (tokens[position].IsIdentifier()) {
      comma_count = 0;
      args.emplace_back(tokens[position].GetString());
    } else if (tokens[position].OperatorMatches(OperatorType::Comma)) {
      comma_count++;
      if (comma_count >= 2) {
        throw std::runtime_error(std::to_string(__LINE__) + " - - - " + __FILE__);
      }
    } else {
      throw std::runtime_error(std::to_string(__LINE__) + " - - - " + __FILE__);
    }
    position++;
  }
  return std::make_pair(args, position);
}


Parser::ParseResult Parser::Parse(const std::vector<Token>& tokens, GlobalContext* context) {
  // Определение или переопределение сущности
  if (std::ranges::contains(tokens, Token{TokenType::Operator, OperatorType::Equal})) {
    // _id_
    if (tokens[0].IsIdentifier()) {
      const std::string& name = tokens[0].GetString();

      std::cout << __LINE__ << '\n';

      // _id_ =
      if (tokens[1].OperatorMatches(OperatorType::Equal)) {

      std::cout << __LINE__ << '\n';


        std::vector<Token> eval(tokens.begin() + 2, tokens.end());
        /* ! */ context->CreateConstant(name, eval);
        return {Type::ConstDeclaration, std::nullopt};
      }

      // _id_(
      if (tokens[1].OperatorMatches(OperatorType::LeftBracket)) {
        // _id_(x, y, z
        auto [args, position] = GetFuncArgs({tokens.begin() + 2, tokens.size() - 2});
        position += 2;
        // _id_(x, y, z)
        if (!tokens[position].OperatorMatches(OperatorType::RightBracket)) {
          throw std::runtime_error(std::to_string(__LINE__) + " - - - " + __FILE__);
        }
        position++;

        // _id_(x, y, z) =
        if (tokens[position].OperatorMatches(OperatorType::Equal)) {
          position++;
          std::vector<Token> eval(tokens.begin() + position, tokens.end());
          /* ! */ context->CreateFunction(name, args, eval);
          return {Type::FunctionDeclaration, std::nullopt};
        }
        // _id_(x, y, z) :
        else if (tokens[position].OperatorMatches(OperatorType::Colon)) {

          std::cout << __LINE__ << '\n';
          

          position++;
          // _id_(x, y, z) : @
          if (tokens[position].OperatorMatches(OperatorType::At)) {
            std::cout << __LINE__ << '\n';


            position++;

            // _id_(x, y, z) : @last
            if (tokens[position].IdentifierMatches("last", "ans", "min", "max", "avg", "step")) {
              const std::string& property = tokens[position].GetString();

              std::cout << __LINE__ << '\n';

              position++;
              // _id_(x, y, z) : @last =
              if (tokens[position].OperatorMatches(OperatorType::Equal)) {
                position++;
                // _id_(x, y, z) : @last = 23.5
                if (tokens[position].IsNumber() && position == tokens.size() - 1) {
                  double value = tokens[position].GetDouble();
                  context->GetFunctionContext(name).AssignProperty(property, value);
                  return {Type::PropertyAssignment, std::nullopt};
                } else {
                  throw std::runtime_error(std::to_string(__LINE__) + " - - - " + __FILE__);
                }
              }
            } else {
              throw std::runtime_error(std::to_string(__LINE__) + " - - - " + __FILE__);
            }
          }
        }
      }
    }

    // $
    else if (tokens[0].OperatorMatches(OperatorType::Dollar)) {
      // $aVar
      if (tokens[1].IsIdentifier()) {
        const std::string& variable = tokens[1].GetString();
        // $aVar =
        if (tokens[2].OperatorMatches(OperatorType::Equal)) {
          // $aVar = 1 + 2
          double value = Evaluator{}.Parse(std::vector<Token>{tokens.begin() + 3, tokens.end()}, context, nullptr);
          /* ! */ context->AssignVariable(variable, value);
          return {Type::VariableAssignment, std::nullopt};
        }
      } else {
        throw std::runtime_error(std::to_string(__LINE__) + " - - - " + __FILE__);
      }
    }

    // @
    else if (tokens[0].OperatorMatches(OperatorType::At)) {
      // @last
      if (tokens[1].IsIdentifier()) {
        const std::string& property = tokens[1].GetString();
        // @last =
        if (tokens[2].OperatorMatches(OperatorType::Equal)) {
          // @last = 0.0
          if (tokens[3].IsNumber() && 3 == tokens.size() - 1) {
            double value = tokens[3].GetDouble();
            /* ! */ context->AssignProperty(property, value);
            return {Type::PropertyAssignment, std::nullopt};
          } else {
            throw std::runtime_error(std::to_string(__LINE__) + " - - - " + __FILE__);
          }
        }
      }
    }
    throw std::runtime_error(std::to_string(__LINE__) + " - - - " + __FILE__);
  }

  // Операция удаление сущности
  // ~
  if (tokens[0].OperatorMatches(OperatorType::Tilde)) {
    // ~_id_
    if (tokens[1].IsIdentifier()) {

      std::cout << __LINE__ << "\n";
      std::cout.flush();

      const std::string& name = tokens[1].GetString();

      // Выражение закончилось
      if (tokens.size() == 2) {
        context->RemoveConstant(name);
        return {Type::DeleteConstVarFunc, std::nullopt};
      }

      // ~_id_(
      if (tokens[2].OperatorMatches(OperatorType::LeftBracket)) {

        std::cout << __LINE__ << "\n";
        std::cout.flush();

        // ~_id_(x, y, z
        auto [args, position] = GetFuncArgs({tokens.begin() + 3, tokens.size() - 3});
        position += 3;
        // ~_id_(x, y, z)
        if (!tokens[position].OperatorMatches(OperatorType::RightBracket)) {
          throw std::runtime_error(std::to_string(__LINE__) + " - - - " + __FILE__);
        }
        position++;

        if (position != tokens.size()) {
          throw std::runtime_error(std::to_string(__LINE__) + " - - - " + __FILE__);
        }

        std::cout << __LINE__ << "\n";
        std::cout.flush();

        context->RemoveFunction(name, args);
        return {Type::DeleteConstVarFunc, std::nullopt};
      } else {
        throw std::runtime_error(std::to_string(__LINE__) + " - - - " + __FILE__);
      }
    }
    // ~$
    else if (tokens[1].OperatorMatches(OperatorType::Dollar)) {
      // ~@_id_
      if (tokens[2].IsIdentifier()) {
        const std::string& name = tokens[2].GetString();

        // Выражение закончилось
        if (tokens.size() == 3) {
          context->RemoveVariable(name);
          return {Type::DeleteConstVarFunc, std::nullopt};
        } else {
          throw std::runtime_error(std::to_string(__LINE__) + " - - - " + __FILE__);
        }
      } else {
        throw std::runtime_error(std::to_string(__LINE__) + " - - - " + __FILE__);
      }
    } else {
      throw std::runtime_error(std::to_string(__LINE__) + " - - - " + __FILE__);
    }
  }

  // Вычисляемое выражение
  Evaluator evaluator;
  return {Type::ExpressionEvaluation, evaluator.Parse(tokens, context, nullptr)};
}