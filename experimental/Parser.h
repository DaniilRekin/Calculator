#pragma once
#include <span>

#include "../import/Token.h"
#include "../import/Lexer.h"

class Act {
  
};

class Arg {

};

class AST {
  class Node {
    std::variant<
      Act, Arg> dt;
    Node* left;
    Node* rigth;
  };

  Node* root_;

 private:
  std::vector<Token> tokens_;
  std::span<Token> viewport_;

 private:
  const Token& Next();
  const Token& Peek();

};

/*
  CodeCraftors
*/