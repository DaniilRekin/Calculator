#pragma once
#include <string>
#include <vector>
#include "Parser.h"

class Constant {
  std::string name_;
  std::vector<Token> eval_;
  mutable bool evaluated_;
  mutable double value_;

 public:
  Constant();
  Constant(const std::string& name, std::vector<Token> eval);

  const std::string& GetName() const;

  double Evaluate() const;

  friend std::ostream& operator<<(std::ostream& os, const Constant& obj);
};

extern std::vector<Constant> constants;