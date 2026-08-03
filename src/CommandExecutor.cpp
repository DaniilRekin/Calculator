#include "../import/CommandExecutor.h"

const std::unordered_map<std::string, CommandExecutor::CommandType> CommandExecutor::cmd{
  {">help", CommandType::Help},
  {">export", CommandType::Export},
  {">import", CommandType::Import},
  {">history", CommandType::History},
  {">clear", CommandType::Clear},
  {">exit", CommandType::Exit}
};

const std::string CommandExecutor::help_msg =
  ("Консольное приложение, позволяющее выполнять инженерные и математические вычисления "
   "с высокой точностью. Программа поддерживает ввод математических выражений, основные "
   "арифметические операции, математические функции и обработку ошибок.\n");

CommandExecutor::CommandType CommandExecutor::Analyze(const std::string& input) {
  auto it = cmd.find(input);
  if (it == cmd.end()) {
    throw std::runtime_error("Исполнительная команда не существует");
  }
  return it->second;
}

std::string CommandExecutor::Execute(CommandExecutor::CommandType command) {
  switch (command) {
    case CommandType::Help: return help_msg;
    case CommandType::Clear: return "\x1b[2J\x1b[3J\x1b[H";
    case CommandType::Export:
#pragma "Недописанный код"
      break;

    case CommandType::Import:
#pragma "Недописанный код"
      break;

    case CommandType::History:
#pragma "Недописанный код"
      break;
      
    case CommandType::Exit: return "Завершение выполнения\n";
    default: throw std::runtime_error("Необработанная команда");
  }
}