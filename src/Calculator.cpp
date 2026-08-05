#include "../import/Calculator.h"

void Calculator::Run() {
  bool stop = false;
  std::string input;

  while (!stop) {
    std::getline(*is_, input);
    try {
      auto type = input_processor_.Analyze(input);

      // Выполнение консольной команды
      if (type == InputProcessor::InputType::Command) {
        auto cmd = cmd_executor_.Analyze(input);
        stop = (cmd == CommandExecutor::CommandType::Exit);
        std::cout << cmd_executor_.Execute(cmd);
      }
      // Выполнение математической логики
      else {
        auto [c, t] = parser_.Parse(lexer_.Tokenize(input), &global_context_);
        if (t.has_value()) {
          *os_ << t.value() << "\n";
        } else {
          //for (const auto& c : constants) { std::cout << c << '\n'; }
          //for (const auto& f : functions) { std::cout << f << '\n'; }
        }
        std::cout << "\n";
      }
    }
    // Обработка исключений
    catch (const Exception& e) {
      *os_ << "\033[31m\033[1m" << e.colored() << "\033[0m" << "\n\n";
    } catch (const std::exception& e) {
      *os_ << "\033[31m\033[1m" << e.what() << "\033[0m" << "\n\n";
    }
  }
}

void Calculator::SetIO(std::istream& is, std::ostream& os) {
  is_ = &is;
  os_ = &os;
}