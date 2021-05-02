#pragma once

#include "Complex.hpp"

class Node {
public:

  int variable;
  Complex terminal;

  Node* zero;
  Node* one;

  Node* parent;

  Node();

  static Node* makeTerminal(Complex terminal);
  bool isTerminal() const;

  static Node* makeVariable(int variable);
  int countNodes() const;
};
