#pragma once
#include <string_view>
#include <unordered_map>
#include <functional>
#include <cmath>
#include <algorithm>

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