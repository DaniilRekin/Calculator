#pragma once
#include <iostream>
#include "InputProcessor.h"
#include "CommandExecutor.h"
#include "Lexer.h"
#include "Parser.h"
#include "Evaluator.h"
#include "Context.h"
#include "History.h"
#include "Importer.h"
#include "Exporter.h"
#include "Exception.h"

class Calculator {
#warning "Исправить"
 public:
  InputProcessor input_processor_;
  CommandExecutor cmd_executor_;
  GlobalContext  global_context_;
  Lexer lexer_;
  Parser parser_;
  Evaluator evaluator_;

  History history_;
  Importer importer_;
  Exporter exporter_;

  std::istream* is_;
  std::ostream* os_;

 public:
  Calculator(std::istream& is = std::cin, std::ostream& os = std::cout) : is_(&is), os_(&os) {
  }

 public:
  void Run();
  void SetIO(std::istream& is, std::ostream& os);
};