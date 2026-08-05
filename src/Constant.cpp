#include "../import/Constant.h"

// std::vector<Constant> constants;

Constant::Constant() : evaluated_(false), value_(0.0) {
}

Constant::Constant(const std::string& name, std::vector<Token> eval) : name_(name), eval_(eval), evaluated_(false), value_(0.0) {
}

const std::string& Constant::GetName() const {
  return name_;
}

double Constant::Evaluate() const {
  if (!evaluated_) {
    Evaluator local_evaluator;
    value_ = local_evaluator.Parse(eval_, context_, nullptr);
    evaluated_ = true; // ! .Parse может бросить исключение
  }

  return value_;
}

void Constant::BindContext(GlobalContext* global_context) {
  this->context_ = global_context;
}

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