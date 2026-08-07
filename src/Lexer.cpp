#include "../import/Lexer.h"
#include "../import/Exception.h"

Lexer::AnalyzeResult Lexer::TryAsOperator(const std::string_view& part) {
  OperatorType op = Token::CharToOperatorType(part.front());
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
  if (ch::is_identifier_first_char(part.front())) {
    while (ch::is_identifier_char(part[count])) {
      count++;
    }
  }

  if (!count) {
    return {AnalyzeResult::UnknowType};
  }

  std::string name{part.begin(), part.begin() + count};
  return {.status = AnalyzeResult::ValidToken,
          .shift = count,
          .token = {.type = TokenType::Identifier, .val = name}};
}

std::vector<Token> Lexer::Tokenize(const std::string& input) {
  std::vector<Token> tokens;
  std::string_view part = input;
  while (part.size()) {
    // Игнорирование пробелов
    if (ch::isspace(part.front())) {
      part.remove_prefix(1);
      continue;
    }

    // Определение типа токена, сохранение его внутреннего значения
    AnalyzeResult parsed;
    if ((parsed = TryAsOperator(part), parsed.status == AnalyzeResult::ValidToken) ||
        (parsed = TryAsNumber(part), parsed.status == AnalyzeResult::ValidToken) ||
        (parsed = TryAsIdentifier(part), parsed.status == AnalyzeResult::ValidToken)) {
      part.remove_prefix(parsed.shift);
      tokens.push_back(std::move(parsed.token));
    } else {
      throw Exception("Undefined token: \n" + input, input.size() - part.size() + 18);
    }
  }
  return tokens;
}