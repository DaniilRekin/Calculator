#pragma once
#include <cstring>
#include <stdexcept>
#include <string>
#include <string_view>

class InputProcessor {
 public:
  enum class InputType { Comment, Command, Statement };
  InputType Analyze(const std::string& input);
};