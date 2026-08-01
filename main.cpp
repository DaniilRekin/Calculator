#include <iostream>
#include "import/Lexer.h"
#include "import/Parser.h"
#include "import/Calculator.h"

int main() {
  Calculator calc(std::cin, std::cout);
  calc.Run();
  return 0;
}