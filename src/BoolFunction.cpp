#include "BoolFunction.hpp"

BoolFunction::BoolFunction() {}

void BoolFunction::append(const Statement& statement) {
  this->statements.push_back(statement);
}

std::ostream& operator<<(std::ostream& os, const BoolFunction& self) {
  if(self.statements.empty()) {
    os << "(empty bool function)";
  } else {
    int size = self.statements.size();
    for(int i = 0; i < size; i++) {
      os << self.statements[i];
      if(i != size - 1) {
        os << " OR ";
      }
    }
  }

  return os;
}

void init_from_node_help(Node* root, Statement statement, BoolFunction* bf) {
  if(root->isTerminal()) {
    bf->append(statement);
  } else {
    if(root->zero) {
      Statement f = statement;
      f.append(Atom(root->variable, false));
      init_from_node_help(root->zero, f, bf);
    }
    if(root->one) {
      Statement f = statement;
      f.append(Atom(root->variable, true));
      init_from_node_help(root->one, f, bf);
    }
  }
}

BoolFunction* BoolFunction::initFromNode(Node* root) {
  BoolFunction* bf = new BoolFunction;
  Statement statement;
  init_from_node_help(root, statement, bf);
  std::cout << "create bf: " << *bf << std::endl;
  return bf;
}

void BoolFunction::simplify() {

}

BoolFunction BoolFunction::operator*(const BoolFunction& other) const {
  return *this;
}

Statement::Statement() {
  this->true_or_false = true;
}

void Statement::append(const Atom& atom) {
  this->atoms.push_back(atom);
}

std::ostream& operator<<(std::ostream& os, const Statement& self) {
  if(self.atoms.size() < 1) {
    os << "(empty statement)";
  } else {
    os << "(";
    for(int i = 0; i < self.atoms.size(); i++) {
      os << self.atoms[i];
      if(i != self.atoms.size() - 1) {
        os << " AND ";
      }
    }
    os << ")";
  }

  return os;
}

Atom::Atom(int variable, bool true_or_false) {
  this->true_or_false = true_or_false;
  this->variable = variable;
}

std::ostream& operator<<(std::ostream& os, const Atom& self) {
  if(self.true_or_false == false) {
    os << "~";
  }
  os << "X" << self.variable;
  return os;
}
