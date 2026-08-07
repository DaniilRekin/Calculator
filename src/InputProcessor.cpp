#include "../import/InputProcessor.h"

#include <iostream>

InputProcessor::InputType InputProcessor::Analyze(const std::string& input) {
  std::string_view view = input;
  while (input.size() && std::isspace(view.front())) {
    view.remove_prefix(1);
  }
  if (!input.size()) {
    throw std::runtime_error("Пустой ввод");
  }
  return (
    view.starts_with("///")  ? InputType::Comment
    : view.starts_with("--") ? InputType::Command
                             : InputType::Statement
  );
}