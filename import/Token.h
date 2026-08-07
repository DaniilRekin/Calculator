#pragma once
#include <string_view>
#include <variant>
#include <vector>
#include <iostream>
#include <stdexcept>

enum class TokenType {
  Number,
  Operator,
  Identifier,
  // #warning "Неиспользуемый токен"
  // EndOfFile,
  Undefined,
};

enum class OperatorType {
  Plus,         // +
  Minus,        // -
  Mult,         // *
  Div,          // /
  Pow,          // ^
  LeftBracket,  // (
  RightBracket, // )

  Comma,        // ,
  Equal,        // =
  At,           // @
  Colon,        // :
  Dollar,       // $
  Tilde,        // ~
  Undefined
};

struct Token {
  TokenType type;
  std::variant<
    double,
    OperatorType, 
    std::string> val;

 public:
  bool operator==(const Token& other) const = default;

 public:
  bool IsNumber() const;
  bool IsOperator() const;
  bool IsIdentifier() const;

 public:
  double GetDouble() const;
  OperatorType GetOperatorType() const;
  const std::string& GetString() const;

 public:
  template <std::same_as<OperatorType>... Ops>
  requires (sizeof...(Ops) > 0)
  bool OperatorMatches(Ops... args) const;

  template <std::convertible_to<std::string_view>... Strs>
  requires (sizeof...(Strs) > 0)
  bool IdentifierMatches(Strs... args) const;

 public:
  static OperatorType CharToOperatorType(char);
  static char OperatorTypeToChar(OperatorType);
};

std::ostream& operator<<(std::ostream& os, OperatorType op);
std::ostream& operator<<(std::ostream& os, const Token& token);
std::ostream& operator<<(std::ostream& os, const std::vector<Token>& tokens);

#include "../src/Token.tpp"