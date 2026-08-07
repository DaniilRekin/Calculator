#include "../import/Constant.h"
#include "../import/Context.h"

const std::unordered_map<std::string, GlobalContext::NullaryFunction> GlobalContext::f0 = {
  {"rand",  [](){ return static_cast<double>(std::rand()) / RAND_MAX; }},
};

const std::unordered_map<std::string, GlobalContext::UnaryFunction> GlobalContext::f1 = {
  {"sin",  std::sin},
  {"cos",  std::cos},
  {"tan", std::tan},
  {"asin", std::asin},
  {"acos", std::acos},
  {"arctan", std::atan},

  {"sqrt", std::sqrt},

  {"abs", std::abs},

  {"exp", std::exp},

  {"log10", std::log10},
  {"log", std::log},

  {"ceil", std::ceil},
  {"floor", std::floor},
  {"round", std::round}
};

const std::unordered_map<std::string, GlobalContext::BinaryFunction> GlobalContext::f2 = {
  {"min", [](double a, double b) { return std::min(a, b); }},
  {"max", [](double a, double b) { return std::max(a, b); }}
};

const std::unordered_map<std::string, double> GlobalContext::c0 = {
  {"pi", std::numbers::pi},
  {"e", std::numbers::e }
};

// --------------------

void GlobalContext::AssignVariable(const std::string& variable, double value) {
  variables[variable] = value;
}

void GlobalContext::AssignProperty(const std::string& property, double value) {
  auto iter = properties.find(property);
  if (iter != properties.end()) {
    iter->second = value;
  } else {
    throw std::runtime_error(std::to_string(__LINE__) + " - - - " + __FILE__);
  }
}

void GlobalContext::CreateFunction(
  const std::string& func,
  const std::vector<std::string>& args,
  const std::vector<Token>& eval
) {
  auto iter = functions.find(func);
  if (iter != functions.end() && iter->second.GetArity() == args.size()) {
    throw std::runtime_error(std::to_string(__LINE__) + " - - - " + __FILE__);
  }

  //
  // Проверка корректности функции
  //

  Function f{func, args, eval};
  f.BindContext(this);
  functions[func] = std::move(f);
  functions[func].name_ = func;
  //functions.insert(std::make_pair(func, f));
}

void GlobalContext::CreateConstant(const std::string& name, const std::vector<Token>& eval) {
  if (constants.contains(name)) {
    throw std::runtime_error(std::to_string(__LINE__) + " - - - " + __FILE__);
  }

  //
  // Проверка корректности константы
  //

  Constant c{name, eval};
  c.BindContext(this);
  constants.insert(std::make_pair(name, c));
}

void GlobalContext::RemoveFunction(const std::string& func, const std::vector<std::string>& args) {
  auto iter = functions.find(func);
  if (iter == functions.end() || iter->second.GetArity() != args.size()) {
    throw std::runtime_error(std::to_string(__LINE__) + " - - - " + __FILE__);
  } else {
    functions.erase(iter);
  }
}

void GlobalContext::RemoveConstant(const std::string& name) {
  auto iter = constants.find(name);
  if (iter == constants.end()) {
    throw std::runtime_error(std::to_string(__LINE__) + " - - - " + __FILE__);
  } else {
    constants.erase(iter);
  }
}

void GlobalContext::RemoveVariable(const std::string& name) {
  auto iter = variables.find(name);
  if (iter == variables.end()) {
    throw std::runtime_error(std::to_string(__LINE__) + " - - - " + __FILE__);
  } else {
    variables.erase(iter);
  }
}

double GlobalContext::GetProperty(const std::string& property) {
  return properties.at(property);
}

double GlobalContext::GetVariable(const std::string& variable) {
  return variables.at(variable);
}

double GlobalContext::GetConstant(const std::string& constant) {
  {
    auto iter = constants.find(constant);
    if (iter != constants.end()) {
      return iter->second.Evaluate();
    }
  }

  {
    auto iter = c0.find(constant);
    if (iter != c0.end()) {
      return iter->second;
    }
  }

  throw std::runtime_error(std::to_string(__LINE__) + " - - - " + __FILE__);
}

double GlobalContext::ExecuteFunction(const std::string& func, std::vector<double> args) {
  auto iter = functions.find(func);
  if (iter != functions.end() && iter->second.GetArity() == args.size()) {
    return iter->second.Evaluate(args);
  }

  switch (args.size()) {
    case 0:
      return f0.at(func)();
    case 1:
      return f1.at(func)(args[0]);
    case 2:
      return f2.at(func)(args[0], args[1]);
  }

  throw std::runtime_error(std::to_string(__LINE__) + " - - - " + __FILE__);
}

void GlobalContext::ResetProperties() {
  for (auto& [key, value] : properties) {
    value = 0.0;
  }
  for (auto& [name, func] : functions) {
    func.local_context_->ResetProperties();
  }
}

void GlobalContext::FreeAll() {
  constants.clear();
  functions.clear();
  variables.clear();
}

LocalContext& GlobalContext::GetFunctionContext(const std::string& func) {
  return functions.at(func).GetContext();
}

void GlobalContext::CreateBasic() {
  properties.insert(std::make_pair<std::string, double>("last", 0.0));
  properties.insert(std::make_pair<std::string, double>("ans", 0.0));
}

// ------------------

void LocalContext::AssignProperty(const std::string& p, double value) {
  properties[p] = value;
}

double LocalContext::GetProperty(const std::string& p) {
  return properties.at(p);
}

void LocalContext::ResetProperties() {
  for (auto& [key, value] : properties) {
    value = 0.0;
  }
}

void LocalContext::CreateBasic() {
  properties["last"] = 0.0;
  properties["min"] = 0.0;
  properties["max"] = 0.0;
  properties["avg"] = 0.0;
  properties["step"] = 0.0;
}