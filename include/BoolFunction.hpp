#pragma once

#include <iostream>
#include <vector>
#include <algorithm>

#include "Node.hpp"
#include "Util.hpp"

class BoolFunction;
class Statement;
class Atom;

class BoolFunction {
public:
  std::vector<Statement> statements;

  BoolFunction();
  void append(const Statement& statement);
  friend std::ostream& operator<<(std::ostream& os, const BoolFunction& self);

  static BoolFunction* initFromNode(Node* root);
  void simplify();

  BoolFunction operator*(const BoolFunction& other);
  bool contains(const BoolFunction& other) const;

  Node* convertToNode() const;
};

class Statement {
public:
  bool true_or_false;
  std::vector<Atom> atoms;

  Statement();
  void append(const Atom& atom);
  friend std::ostream& operator<<(std::ostream& os, const Statement& self);
  bool contains(const Statement& other) const;
  bool contains(const Atom& other) const;
};

class Atom {
public:
  bool true_or_false;
  int variable;

  Atom(int variable, bool true_or_false = true);
  bool operator==(const Atom& other) const;
  friend std::ostream& operator<<(std::ostream& os, const Atom& self);
  bool operator<(const Atom& other) const;
};
