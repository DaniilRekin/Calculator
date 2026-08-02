#pragma once
#include <iostream>
#include "Lexer.h"
#include "Parser.h"
#include "History.h"
#include "Memory.h"
#include "Importer.h"
#include "Exception.h"
#include "Analyzer.h"

class Calculator {
  Lexer lexer_;
  Analyzer analyzer_;

  History history_;
  Memory memory_;
  Importer import_;

  std::istream* is_;
  std::ostream* os_;

 private:
  void PrintHelp();

 public:
  Calculator(std::istream& is = std::cin, std::ostream& os = std::cout) : is_(&is), os_(&os) {
  }

 public:
  void Run();
  void SetIO(std::istream& is, std::ostream& os);
};