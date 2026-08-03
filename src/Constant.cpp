#include "../import/Constant.h"

std::vector<Constant> constants;

Constant::Constant() : evaluated_(false), value_(0.0) {
}

Constant::Constant(const std::string& name, std::vector<Token> eval) : name_(name), eval_(eval), evaluated_(false), value_(0.0) {
}

const std::string& Constant::GetName() const {
  return name_;
}

double Constant::Evaluate() const {
  if (!evaluated_) {
    Parser local_parser;
    value_ = local_parser.Parse(eval_);
    evaluated_ = true; // ! .Parse может бросить исключение
  }

  return value_;
}