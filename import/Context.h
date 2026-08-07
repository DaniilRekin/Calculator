#pragma once
#include <string_view>
#include <unordered_map>
#include "Token.h"
#include "Constant.h"
#include "Function.h"

class Constant;
class Function;

class LocalContext;

class GlobalContext {
  using NullaryFunction = double(*)();
  using UnaryFunction = double(*)(double);
  using BinaryFunction = double(*)(double, double);
  using TernaryFunction = double(*)(double, double, double);

  // Стандартные функции и константы
  static const std::unordered_map<std::string, NullaryFunction> f0;
  static const std::unordered_map<std::string, UnaryFunction> f1;
  static const std::unordered_map<std::string, BinaryFunction> f2;
  static const std::unordered_map<std::string, double> c0;

#warning "Исправить"
 public:
  std::unordered_map<std::string, double> properties;
  std::unordered_map<std::string, double> variables;
  std::unordered_map<std::string, Constant> constants;
  std::unordered_map<std::string, Function> functions;

 public:
  void AssignVariable(const std::string& id, double value);
  void AssignProperty(const std::string& id, double value);

 public:
  void CreateFunction(
    const std::string& name,
    const std::vector<std::string>& args,
    const std::vector<Token>& eval);

  void CreateConstant(
    const std::string& name,
    const std::vector<Token>& eval);

 public:
  void RemoveFunction(const std::string& name, const std::vector<std::string>& args);
  void RemoveConstant(const std::string& name);
  void RemoveVariable(const std::string& name);

 public:
  double GetProperty(const std::string& property);
  double GetVariable(const std::string& variable);
  double GetConstant(const std::string& constant);

 public:
  double ExecuteFunction(const std::string& func, std::vector<double> args);

 public:
  void ResetProperties();
  void FreeAll();

 public:
  LocalContext& GetFunctionContext(const std::string& func);

 public:
  void CreateBasic();
};

class LocalContext {
  std::unordered_map<std::string, double> properties;

 public:
  void AssignProperty(const std::string& p, double value);
  double GetProperty(const std::string& p);

  void ResetProperties();

  void CreateBasic();
};