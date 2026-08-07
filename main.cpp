#define RELEASE 0

#if RELEASE == 1

#include <iostream>

#include "import/Calculator.h"
#include "import/Exception.h"
#include "import/Function.h"
#include "import/Lexer.h"
#include "import/Parser.h"

int main() {
  Calculator calc(std::cin, std::cout);
  calc.Run();

  return 0;
}

#else

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <vector>

#include "import/Calculator.h"

//--------------------------------------------------
// Параметры экрана
//--------------------------------------------------

constexpr int WIDTH = 1000;
constexpr int HEIGHT = 400;

//--------------------------------------------------
// Параметры отображения
//--------------------------------------------------

constexpr int ORIGIN_X = WIDTH / 2;
constexpr int ORIGIN_Y = HEIGHT / 2;

constexpr double ZOOM = 0.20;  // >1 - приближение, <1 - отдаление

constexpr double BASE_SCALE_X = 0.15 / 50.0;
constexpr double BASE_SCALE_Y = HEIGHT * 0.4;

//--------------------------------------------------
// Буфер изображения
//--------------------------------------------------
using Color = uint8_t;

constexpr Color COLOR_NONE = 0;
constexpr Color COLOR_AXIS = 1;
constexpr Color COLOR_RED = 2;
constexpr Color COLOR_GREEN = 3;
constexpr Color COLOR_BLUE = 4;
constexpr Color COLOR_YELLOW = 5;
constexpr Color COLOR_MAGENTA = 6;
constexpr Color COLOR_CYAN = 7;

std::vector<std::vector<Color> > screen(HEIGHT, std::vector<Color>(WIDTH, COLOR_NONE));

void drawPixel(int x, int y, Color color) {
  if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
    screen[y][x] = color;
  }
}

//--------------------------------------------------
// Алгоритм Брезенхема
//--------------------------------------------------
void drawLine(int x0, int y0, int x1, int y1, Color color) {
  int dx = std::abs(x1 - x0);
  int dy = std::abs(y1 - y0);

  int sx = (x0 < x1) ? 1 : -1;
  int sy = (y0 < y1) ? 1 : -1;

  int err = dx - dy;

  while (true) {
    drawPixel(x0, y0, color);

    if (x0 == x1 && y0 == y1) break;

    int e2 = err * 2;

    if (e2 > -dy) {
      err -= dy;
      x0 += sx;
    }

    if (e2 < dx) {
      err += dx;
      y0 += sy;
    }
  }
}

void DrawFunction(Calculator& calc, const std::string& name, Color color) {
  int prevX = -1;
  int prevY = -1;

  for (int x = 0; x < WIDTH; ++x) {
    double mathX = (x - ORIGIN_X) * (BASE_SCALE_X / ZOOM);
    
    std::cout << calc.global_context_.functions.size();
    std::cout << calc.global_context_.functions["f"].GetName();
    double mathY = calc.global_context_.ExecuteFunction(name, {mathX});
    int y = ORIGIN_Y - static_cast<int>(mathY * BASE_SCALE_Y * ZOOM);

    if (prevX >= 0) drawLine(prevX, prevY, x, y, color);

    prevX = x;
    prevY = y;
  }
}

struct Graph {
  std::string name;
  Color color;
};

int main() {
  Calculator calc;
  calc.Run();
  std::cout << "\n\n";

  //--------------------------------------------------
  // Оси координат
  //--------------------------------------------------
  drawLine(0, ORIGIN_Y, WIDTH - 1, ORIGIN_Y, COLOR_AXIS);
  drawLine(ORIGIN_X, 0, ORIGIN_X, HEIGHT - 1, COLOR_AXIS);

  int prevX = -1;
  int prevY = -1;

  //--------------------------------------------------
  // Построение графика
  //--------------------------------------------------

  std::string str;
  std::vector<Graph> graphs;
  do {
    std::cin >> str;
    if (str != "=") {
      graphs.emplace_back(str, 2 + graphs.size());
    }
  } while (str != "=");

  for (const auto& graph : graphs) {
    DrawFunction(calc, graph.name, graph.color);
  }

  std::cout << "\033Pq";
  std::cout << "#1;2;200;200;200";      // черный
  std::cout << "#2;2;100;0;0";    // красный
  std::cout << "#3;2;0;100;0";    // зеленый
  std::cout << "#4;2;0;0;100";    // синий
  std::cout << "#5;2;100;100;0";  // желтый
  std::cout << "#6;2;100;0;100";  // пурпурный
  std::cout << "#7;2;0;100;100";  // голубой
  for (int sliceY = 0; sliceY < HEIGHT; sliceY += 6) {
    for (Color color = COLOR_AXIS; color <= COLOR_CYAN; ++color) {
      std::cout << "#" << int(color);

      for (int x = 0; x < WIDTH; ++x) {
        int sixelByte = 0;

        for (int bit = 0; bit < 6; ++bit) {
          int y = sliceY + bit;

          if (y < HEIGHT && screen[y][x] == color) sixelByte |= 1 << bit;
        }

        std::cout << char(sixelByte + 63);
      }

      std::cout << "$";  // следующий цвет начинается с начала той же строки
    }

    std::cout << "-";  // следующая шестипиксельная строка
  }

  std::cout << "\033\\\n";

  return 0;
}

#endif

/*
  C = 6.0         объявление функции
  f(x) = x^x      объявление константы
  $var = pi ^ pi  объявление переменной

  $var = $var^2   обновление значения переменной
  @last = 0       обновление значения глобального свойства
  f(x):@last = 0  обновление значения локального свойства

  ~C              удаление константы
  ~f(x)           удаление функции
  ~$var           удаление переменной
*/

/*
  --help          справка о возможностях
  --export .math  экспорт сущностей
  --import .math  импорт сущностей
  --history       история вычислений
  --clear         очистка терминала
  --exit          завершение работы

  --precision 9   установка количества знаков в десятичных дробях при выводе

  --reset-prop    сброс всех глобальных и локальных свойств
  --free-all      удаление всех объявленных функций, констант и переменных

  --func-list     список объявленных функций
  --const-list    список объявленных констант
  --var-list      список объявленных переменных
  --prop-list     список всех глобальных и локальных свойств

  --std-list      список всех стандартных констант и функций
*/

/*
  @last   последнее глобальное или локальное вычисленное значение
  @ans    последнее глобальное вычисленное значение

  @step   количество вызовов функции
  @min    минимальное значение, которое возвращала функция
  @max    максимальное значение, которое возвращала функция
  @avg    среднее значение от всех вызовов функции
*/

/*

  Построение графика
  #graph [-5:5, 0.01]
    sin(x)
    cos(x)

  Построение таблицы
  #table [-5:5, 0.5]

  Решение уравнения
  #equation x = x + 2

  Область определения функции
  #domain sqrt(x-5)

  Информация об объекте
  #info f(x)

  Производная
  #diff x^3

  Интеграл
  #integral sin(x) [0; pi]

  Решение системы уравнений
  #system {
    x = y + 2
    2x = y
  }
*/


/*
  **Реализовано**
  - основные математические операторы: + - * / ^
  - основные математические функции: sin(x), cos(x)...
  - динамическое объявление и удаление функций, констант, переменных
  - присвоение и чтение значений атрибутов и функций

  ------------------------------------------------------------

  **Начало**
  - рефакторинг кода
  - обновление README.md и TODO.md
  - вывод сообщений об ошибках

  **Синтаксис**
  * Комментарии вида ///

  **Обработка ошибок**
  - исполнитель команд         (CommandExecutor)
  - парсер                     (Parser)
  - вычислитель                (Evaluator)
  - функции с ограниченной ОДЗ (Function)

  **Функции**
  - добавление функции sgn, функций rad и deg, trunc, frac
  - функции min, max, avg, median с переменным количеством аргументов
  - добавление атрибутов @diff_x..., @diff_res и сокращённых @dx, @df
  - корректное вычисление атрибутов функций (@avg, @min, @step)
  - корректная обработка функций с ограниченной областью значений (sqrt...)
  - ?факториал, остаток от деления

  **Взаимодействие с пользователем**
  - вывод справки о возможностях программы
  - управление настройками
  - работа с .json файлами конфигурации
  - история рассчётов
  - экспорт и импорт сущностей

  **Преобразование и исполнение**
  - использование AST, вместо рекурсивных вызовов
  - вывод зависимостей функций и констант
  - безопасная обработка зависимости констант и функций от других сущностей
  - пошаговый вывод рассчётов

  **Графический интерфейс**
  - переход из CLI в GUI интерфейс, SFML
  - возможность строить графики функций(*)
  - вывод графиков функций в .png файл
  - ввод синтакиса формул с подсветкой

  **Рекуррентные функции**
  - Определение и вычисление функций:
    fact(0) = 1
    fact(1) = 1
    fact(n) = n * fact(n - 1)

  **Уравнения**
  - возможность решать линейные уравнения
  - возможность решать квадратные уравнения
  - возможность решать уравнения n-ой степени
  - операции над списками значений, отрезками, интервалами

  **Вывод свойств функций**
  - вывод свойств функции
  - корректный вывод графиков

  **Использование классов чисел**
  - Математический класс Decimal
  - Класс чисел Complex
*/

/*
 READY:
  * Utils.h
    Utils.cpp

  * InputProcessor.h
    InputProcessor.cpp

  : CommandExecutor.h   (50%)
    CommandExecutor.cpp

  Token

  * Lexer.h
    Lexer.cpp




*/

/*
  https://chatgpt.com/s/t_6a757efa0814819197f932e5590aae89
*/

/*
  /// Функция сигмоиды
  sigm(x) = 1 / (1 + e^-x)

  /// Шаг изменения x
  dx = 0.01

  /// Производная сигмоиды по dx
  derivative(x) = (sigm(x) - sigm(x - dx)) / dx

  /// --------------------------

  /// Синусоида
  f(x) = sin(max(0, x))

  /// Шаг измения dx при построении графика
  dx = 0.015

  /// Определённый интеграл
  g(x) = @last + f(x) * dx

*/