#include "../import/Calculator.h"

void Calculator::Run() {
  std::string str;

  while (true) {
    std::getline(*is_, str);
    if (str == "=") {
      break;
    }

    try {
      *os_ << parser_.Parse(lexer_.Tokenize(str)) << "\n\n";
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