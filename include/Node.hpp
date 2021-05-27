#pragma once
#include <set>

#include "Complex.hpp"

class Node {
public:

  int variable;
  Complex terminal;

  Node* zero;
  Node* one;

  Node* parent;

  int count;
  std::set<int>* variables;

  Node();

  static Node* makeTerminal(Complex terminal);
  bool isTerminal() const;

  static Node* makeVariable(int variable);
  int countNodes() const;

  // algorithm entry
  // table: 2Darray(x * y)
  // n: the variable count
  static Node* initWithTable(char** table, int x, int y, int n);

  bool operator==(const Node& other) const;

  static Node* makePrefix(const std::vector<int>& counts, const std::vector<std::set<int>>& variables, Complex terminal);
  static Node* findTerminal(Node* root);
};
