#pragma once
#include <charconv>
#include <string>
#include <string_view>
#include <vector>

#include "Token.h"
#include "Utils.h"

class Lexer {
  struct AnalyzeResult {
    enum Status { UnknowType, InvalidToken, ValidToken };

    Status status = UnknowType;
    size_t shift = 0;
    Token token = {};
  };

 private:
  AnalyzeResult TryAsNumber(const std::string_view& part);
  AnalyzeResult TryAsOperator(const std::string_view& part);
  AnalyzeResult TryAsIdentifier(const std::string_view& part);

 public:
  std::vector<Token> Tokenize(const std::string& input);
};