#include <iostream>
#include "import/Lexer.h"
#include "import/Parser.h"
#include "import/Calculator.h"
#include "import/Exception.h"
#include "import/Function.h"

/*
  --help
  --export file.math
  --import file.math
  --history
  --clear
  --exit / --quit
  

*/

int main() {
  Calculator calc(std::cin, std::cout);
  calc.Run();

  return 0;
}