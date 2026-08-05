// Token.tpp

template <std::same_as<OperatorType>... Ops>
requires(sizeof...(Ops) > 0)
bool Token::OperatorMatches(Ops... args) const {
  return type == TokenType::Operator && ((args == std::get<OperatorType>(val)) || ...);
}

template <std::convertible_to<std::string_view>... Strs>
requires(sizeof...(Strs) > 0)
bool Token::IdentifierMatches(Strs... args) const {
  return type == TokenType::Identifier && ((args == std::get<std::string>(val)) || ...);
}