#include <iostream>
#include "import/Lexer.h"
#include "import/Parser.h"
#include "import/Calculator.h"

#include "import/Exception.h"

// Последовательность файлов
// Utils.h
//   Utils.cpp

// Token.h

// Lexer.h
//   Lexer.cpp

int main() {
  Calculator calc(std::cin, std::cout);
  calc.Run();
  return 0;
}