#include "../import/Function.h"

Function::Function() {
  local_context_ = std::make_unique<LocalContext>();
  local_context_->CreateBasic();
}

Function::Function(std::string name, std::vector<std::string> args, std::vector<Token> eval)
    : name_(name), args_(args), eval_(eval) {
  local_context_ = std::make_unique<LocalContext>();
  local_context_->CreateBasic();
}

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
      auto pos = std::find(args_.begin(), args_.end(), std::get<std::string>(eval_[i].val));
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

  Evaluator evaluator;
  double value = evaluator.Parse(tokens, global_context_, local_context_.get());

  local_context_->AssignProperty("last", value);
  local_context_->AssignProperty("min", std::min(value, local_context_->GetProperty("min")));
  local_context_->AssignProperty("max", std::max(value, local_context_->GetProperty("max")));
  local_context_->AssignProperty("step", std::max(value, local_context_->GetProperty("step") + 1));

  return value;
}

void Function::BindContext(GlobalContext* global_context) {
  global_context_ = global_context;
}

LocalContext& Function::GetContext() {
  return *local_context_;
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