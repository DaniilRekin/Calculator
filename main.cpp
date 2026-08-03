#include <iostream>
#include "import/Lexer.h"
#include "import/Parser.h"
#include "import/Calculator.h"
#include "import/Exception.h"
#include "import/Function.h"

/*
  C = 6.0

  f(x) = x^x
*/

/*
  --help
  --export file.math
  --import file.math
  --history
  --clear
  --exit
  --set-prec
  --reset: сброс переменных @last
  --free:  удаление функций и переменных
  --graph f=sin(x) d=[-5;5] s=0.1
*/

/*
  FIX:
  - ✓проблемы с памятью
  - локальные значения @last не должны дублироваться
  - рефакторинг кода
  - обновление README.md и TODO.md

  TODO:
  - идентификатор @last
  - история рассчётов

  TODO:
  - возможность строить графики функций
  - пошаговый вывод рассчётов

  - возможность решать линейные уравнения
  - возможность решать квадратные уравнения
  - возможность решать системы уравнений

  - рассчёты с использованием собственного класса Decimal для десятичных дробей
  - использование класса Fraction для обыкновенных дробей
  - класс Complex, поддержка комплексных чисел
*/

/*
 READY:
  * InputProcessor.h
    InputProcessor.cpp
  
  : CommandExecutor.h   (!команды с параметрами)
    CommandExecutor.cpp
  
  * Lexer.h
    Lexer.cpp

  

  
*/

int main() {
  Calculator calc(std::cin, std::cout);
  calc.Run();

  return 0;
}