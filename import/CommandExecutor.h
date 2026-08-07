#pragma once
#include <format>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>
#include <algorithm>
#include <ostream>
#include <iomanip>
#include "Context.h"
#include "Settings.h"

class CommandExecutor {
 public:
  enum class CommandType {
    // Команды управления
    Help, Clear, Exit,
    // Взаимодействие с памятью
    Export, Import, History,
    // Установка точности вывода
    Precision,
    // Сброс значений свойств
    ResetProperties,
    // Удаление всех сущностей
    FreeAll,
    // Списки сущностей
    FuncList, ConstList, VarsList, PropList,
    // Список стандартных функций
    StdList,

    // Неустановленная команда
    Undefined
  };

 private:
  static const std::vector<std::pair<std::string, CommandExecutor::CommandType>> cmd;
  static const std::string help_msg;

 private:
  std::ostream& os_;
  GlobalContext& context_;
  Settings& settings_;
  

 public:
  CommandExecutor(std::ostream& os, GlobalContext& context, Settings& settings);

 public:
  CommandType Execute(const std::string& input);
};