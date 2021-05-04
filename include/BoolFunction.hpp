#pragma once

#include <iostream>
#include <vector>

class BoolFunction;
class Statement;
class Atom;

class BoolFunction {
public:
  std::vector<Statement> statements;

  BoolFunction();
  void append(const Statement& statement);
  friend std::ostream& operator<<(std::ostream& os, const BoolFunction& self);
};

class Statement {
public:
  bool true_or_false;
  std::vector<Atom> atoms;

  Statement();
  void append(const Atom& atom);
  friend std::ostream& operator<<(std::ostream& os, const Statement& self);
};

class Atom {
public:
  bool true_or_false;
  int variable;

  Atom(int variable, bool true_or_false = true);
  friend std::ostream& operator<<(std::ostream& os, const Atom& self);
};
