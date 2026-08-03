#pragma once
#include <stdexcept>
#include <string>
#include <unordered_map>

class CommandExecutor {
 public:
  enum class CommandType { Help, Export, Import, History, Clear, Exit, Undefined };
 
 private:
  static const std::unordered_map<std::string, CommandType> cmd;
  static const std::string help_msg;

 public:
  CommandType Analyze(const std::string& input);
  std::string Execute(CommandType command);
};