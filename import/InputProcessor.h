#pragma once

#include <string>
#include <unordered_map>
#include <stdexcept>
#include <format>

class InputProcessor {
 public:
  enum class InputType { Command, Statement };
  InputType Analyze(const std::string& input);
};