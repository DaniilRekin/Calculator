#pragma once
#include <string>
#include <vector>
#include "Token.h"
#include "Parser.h"
#include "Context.h"

class GlobalContext;

class Constant {
  std::string name_;
  std::vector<Token> eval_;
  GlobalContext* context_;
  mutable bool evaluated_;
  mutable double value_;

 public:
  Constant();
  Constant(const std::string& name, std::vector<Token> eval);

 public:
  bool operator==(const Constant& other) const = default;

  const std::string& GetName() const;
  double Evaluate() const;

  void BindContext(GlobalContext* global_context);

  friend std::ostream& operator<<(std::ostream& os, const Constant& obj);
};