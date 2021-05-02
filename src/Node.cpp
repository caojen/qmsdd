#include "Node.hpp"

Node::Node() {
  this->variable = 0;
  this->terminal = 0;
  this->zero = nullptr;
  this->one = nullptr;
  this->parent = nullptr;
}

Node* Node::makeTerminal(Complex terminal) {
  Node* ret = new Node;

  ret->variable = -1;
  ret->terminal = terminal;
  ret->zero = nullptr;
  ret->one = nullptr;
  ret->parent = nullptr;

  return ret;
}

bool Node::isTerminal() const {
  return this->variable == -1;
}

Node* Node::makeVariable(int variable) {
  Node* ret = new Node;

  ret->variable = variable;
  ret->terminal = -1;
  ret->zero = nullptr;
  ret->one = nullptr;
  ret->parent = nullptr;

  return ret;
}
