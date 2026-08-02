#include "../import/Calculator.h"

void Calculator::Run() {
  std::string str;

  while (true) {
    std::getline(*is_, str);
    if (str == "=") {
      break;
    }

    try {
      auto t = analyzer_.Analyze(lexer_.Tokenize(str));
      if (t.has_value()) {
        *os_ << t.value() << "\n\n";
      } else {
        /*
        for (const auto& c : constants) {
          std::cout << c << '\n';
        }

        for (const auto& f : functions) {
          std::cout << f << '\n';
        }*/

        std::cout << "\n";
      }
    } catch (const Exception& e) {
      *os_ << e.colored() << "\n\n";
    } catch (const std::exception& e) {
      *os_ << e.what() << "\n\n";
    }

  }
}

void Calculator::SetIO(std::istream& is, std::ostream& os) {
  is_ = &is;
  os_ = &os;
}

void Calculator::PrintHelp() {
  *os_ << "Info:";
}