#include "../import/Constant.h"

std::vector<Constant> constants;

double Constant::Evaluate() const {
  Parser local_parser;
  return local_parser.Parse(eval_);
}