#pragma once
#include <unordered_map>
#include <algorithm>
#include <string>
#include <vector>
#include <memory>
#include "Context.h"
#include "Parser.h"
#include "Token.h"

class GlobalContext;
class LocalContext;

class Function {
#warning "Исправить"
 public:
  std::string name_;
  std::vector<std::string> args_;
  std::vector<Token> eval_;
  GlobalContext* global_context_;
  std::unique_ptr<LocalContext> local_context_;

 public:
  Function();

  Function(std::string name, std::vector<std::string> args, std::vector<Token> eval);

 public:
  

  const std::string& GetName() const;
  size_t GetArity() const;

 public:
  double Evaluate(std::vector<double> values) const;

  friend std::ostream& operator<<(std::ostream& os, const Function& obj);

 public:
  void BindContext(GlobalContext* global_context);

  LocalContext& GetContext();
  
};

// extern std::vector<Function> functions;