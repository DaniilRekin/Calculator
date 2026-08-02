#pragma once
#include <algorithm>
#include <string>
#include <vector>

#include "Parser.h"
#include "Token.h"

class Function {
  std::string name_;
  std::vector<std::string> args_;
  std::vector<Token> eval_;

 public:
  Function() = default;

  Function(std::string name, std::vector<std::string> args, std::vector<Token> eval);

 public:
  const std::string& GetName() const;
  size_t GetArity() const;

 public:
  double Evaluate(std::vector<double> values) const;

  friend std::ostream& operator<<(std::ostream& os, const Function& obj);
};

extern std::vector<Function> functions;