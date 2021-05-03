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

  // algorithm entry
  // table: 2Darray(x * y)
  // n: the variable count
  static Node* initWithTable(char** table, int x, int y, int n);
};
