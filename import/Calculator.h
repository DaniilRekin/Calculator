#pragma once
#include <iostream>

#include "CommandExecutor.h"
#include "Context.h"
#include "Evaluator.h"
#include "Exception.h"
#include "Exporter.h"
#include "History.h"
#include "Importer.h"
#include "InputProcessor.h"
#include "Lexer.h"
#include "Parser.h"
#include "Utils.h"

class Calculator {
#warning "Исправить"
 public:
  std::istream* is_;
  std::ostream* os_;

  Settings settings_;

  GlobalContext global_context_;
  InputProcessor input_processor_;
  CommandExecutor command_executor_;
  Lexer lexer_;
  Parser parser_;
  Evaluator evaluator_;

  History history_;
  Importer importer_;
  Exporter exporter_;

 public:
  Calculator(std::istream& is = std::cin, std::ostream& os = std::cout)
     : is_(&is), os_(&os), global_context_(), command_executor_(*os_, global_context_, settings_)
  {
  }

 public:
  void Run();
  void SetIO(std::istream& is, std::ostream& os);
};