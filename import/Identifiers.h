#pragma once
#include <string_view>
#include <unordered_map>
#include <functional>
#include <cmath>
#include <algorithm>

using NullaryFunction = double(*)();
using UnaryFunction = double(*)(double);
using BinaryFunction = double(*)(double, double);
using TernaryFunction = double(*)(double, double, double);

static const std::unordered_map<std::string_view, NullaryFunction> f0 = {
  {"rand",  [](){ return static_cast<double>(std::rand()) / RAND_MAX; }},
};

static const std::unordered_map<std::string_view, UnaryFunction> f1 = {
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

static const std::unordered_map<std::string_view, BinaryFunction> f2 = {
  {"min", [](double a, double b) { return std::min(a, b); }},
  {"max", [](double a, double b) { return std::max(a, b); }}
};

static const std::unordered_map<std::string_view, double> constants = {
  {"pi", std::numbers::pi},
  {"e", std::numbers::e }
};

/*
double EvalFunc(const std::string_view& str, const std::vector<double>& args) {
  if (args.size() == 0) {
    return f0.at(str)();
  }

  if (args.size() == 1) {
    return f1.at(str)(args[0]);
  }

  if (args.size() == 2) {
    return f2.at(str)(args[0], args[1]);
  }
}*/