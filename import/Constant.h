#pragma once
#include <string>
#include <vector>
#include "Parser.h"

struct Constant {
  std::string name_;
  std::vector<Token> eval_;

  friend std::ostream& operator<<(std::ostream& os, const Constant& obj);

  double Evaluate() const;
};

extern std::vector<Constant> constants;