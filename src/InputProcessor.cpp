#include "../import/InputProcessor.h"

InputProcessor::InputType InputProcessor::Analyze(const std::string& input) {
  return input.starts_with('>') ? InputType::Command : InputType::Statement;
}