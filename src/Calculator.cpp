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
        auto cmd = command_executor_.Execute(input);
        stop = (cmd == CommandExecutor::CommandType::Exit);
      }
      // Выполнение математической логики
      else if (type == InputProcessor::InputType::Statement) {
        auto tk = lexer_.Tokenize(input);
        std::cout << __LINE__ << '\n';
        std::cout.flush();
        //std::cout << tk << '\n';
        std::cout << __LINE__ << '\n';
        std::cout.flush();
        auto [c, t] = parser_.Parse(lexer_.Tokenize(input), &global_context_);
        if (t.has_value()) {
          *os_ << Format(t.value(), settings_.precision) << "\n";
        } else {
          //for (const auto& c : constants) { std::cout << c << '\n'; }
          //for (const auto& f : functions) { std::cout << f << '\n'; }
        }
        std::cout << "\n";
      } else {
        // Введён комментарий...
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