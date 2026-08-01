#include "../import/Lexer.h"
#include "../import/Exception.h"

Lexer::AnalyzeResult Lexer::TryAsOperator(const std::string_view& part) {
  auto charTable = [](char ch) {
    switch (ch) {
      case '(': return OperatorType::LeftBracket;
      case ')': return OperatorType::RightBracket;
      case '+': return OperatorType::Plus;
      case '-': return OperatorType::Minus;
      case '*': return OperatorType::Mult;
      case '/': return OperatorType::Div;
      case '^': return OperatorType::Pow;
      case ',': return OperatorType::Comma;
      default: return OperatorType::Undefined;
    }
  };

  OperatorType op = charTable(part.front());
  if (op == OperatorType::Undefined) {
    return {AnalyzeResult::UnknowType};
  }

  return {.status = AnalyzeResult::ValidToken,
          .shift = 1,
          .token = {.type = TokenType::Operator, .val = op}};
}

Lexer::AnalyzeResult Lexer::TryAsNumber(const std::string_view& part) {
  // Парсинг double
  double value = 0.0;
  auto res = std::from_chars(part.data(), part.data() + part.size(), value);

  // Тип не совпал
  if (res.ec != std::errc()) {
    return {AnalyzeResult::UnknowType};
  }

  // Парсинг произошёл
  return AnalyzeResult{.status = AnalyzeResult::ValidToken,
                       .shift = static_cast<size_t>(res.ptr - part.data()),
                       .token = {.type = TokenType::Number, .val = value}};
}

Lexer::AnalyzeResult Lexer::TryAsIdentifier(const std::string_view& part) {
  size_t count = 0;
  if (IsAlpha(part.front())) {
    while (IsIdentifierChar(part[count])) {
      count++;
    }
  }

  if (!count) {
    return {AnalyzeResult::UnknowType};
  }

  return {.status = AnalyzeResult::ValidToken,
          .shift = count,
          .token = {.type = TokenType::Identifier, .val = part.substr(0, count)}};
}

std::vector<Token> Lexer::Tokenize(const std::string& input) {
  std::vector<Token> tokens;
  std::string_view part = input;
  while (part.size()) {
    // Игнорирование пробелов
    if (IsSpace(part.front())) {
      part.remove_prefix(1);
      continue;
    }

    // Определение токена
    AnalyzeResult parsed;
    if ((parsed = TryAsOperator(part), parsed.status == AnalyzeResult::ValidToken) ||
        (parsed = TryAsNumber(part), parsed.status == AnalyzeResult::ValidToken) ||
        (parsed = TryAsIdentifier(part), parsed.status == AnalyzeResult::ValidToken)) {
      part.remove_prefix(parsed.shift);
      tokens.push_back(parsed.token);
    } else {
      throw Exception("Undefined token: \n" + input, input.size() - part.size() + 18);
    }
  }
  return tokens;
}