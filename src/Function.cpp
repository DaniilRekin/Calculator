#include "../import/Function.h"

std::vector<Function> functions;

Function::Function(std::string name, std::vector<std::string> args, std::vector<Token> eval)
  : name_(name), args_(args), eval_(eval) {}

const std::string& Function::GetName() const {
  return name_;
}

size_t Function::GetArity() const {
  return args_.size();
}

double Function::Evaluate(std::vector<double> values) const {
  if (values.size() != args_.size()) {
    throw Exception("Некорректное количество параметров функции");
  }

  std::vector<Token> tokens(eval_.size());
  for (size_t i = 0; i < eval_.size(); i++) {
    bool replaced = false;
    if (eval_[i].type == TokenType::Identifier) {
      auto pos = std::find(args_.begin(), args_.end(), std::get<std::string_view>(eval_[i].val));
      if (pos != args_.end()) {
        size_t param_idx = pos - args_.begin();
        tokens[i].type = TokenType::Number;
        tokens[i].val = values[param_idx];
        replaced = true;
      }
    }

    if (!replaced) {
      tokens[i] = eval_[i];
    }
  }

  Parser local_parser;
  return local_parser.Parse(tokens);
}

std::ostream& operator<<(std::ostream& os, const Function& obj) {
    os << "Name: " << obj.name_ << '\n';

    os << "Args: [";
    for (size_t i = 0; i < obj.args_.size(); ++i) {
      if (i > 0) os << ", ";
      os << '"' << obj.args_[i] << '"';
    }
    os << "]\n";

    os << "Eval: [";
    for (size_t i = 0; i < obj.eval_.size(); ++i) {
      if (i > 0) os << ", ";
      os << obj.eval_[i];
    }
    os << "]";

    return os;
  }