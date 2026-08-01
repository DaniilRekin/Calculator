#pragma once
#include <string_view>
#include <unordered_map>
#include <functional>
#include <cmath>

using UnaryFunction = std::function<double(double)>;
static const std::unordered_map<std::string_view, UnaryFunction> functions = {
  {"sin",  [](double x) { return std::sin(x); }},
  {"cos",  [](double x) { return std::cos(x); }},
  {"tan", [](double x) { return std::tan(x); }},
  {"asin", [](double x) { return std::asin(x); }},
  {"acos", [](double x) { return std::acos(x); }},
  {"arctan", [](double x) { return std::atan(x); }},

  {"sqrt", [](double x) { return std::sqrt(x); }},

  {"abs", [](double x) { return std::abs(x); }},

  {"exp", [](double x) { return std::exp(x); }},

  {"log10", [](double x) { return std::log10(x); }},
  {"log", [](double x) { return std::log(x); }},

  {"ceil", [](double x) { return std::ceil(x); }},
  {"floor", [](double x) { return std::floor(x); }},
  {"round", [](double x) { return std::round(x); }},

  {"rand", [](double x) { return static_cast<double>(std::rand()) / RAND_MAX; }}
};

static const std::unordered_map<std::string_view, std::function<double()>> constants = {
  {"pi", [] { return std::numbers::pi; }},
  {"e",  [] { return std::numbers::e; }}
};