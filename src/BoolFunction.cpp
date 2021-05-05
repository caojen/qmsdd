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
  // std::cout << "create bf: " << *bf << std::endl;
  return bf;
}

void BoolFunction::simplify() {
  std::cout << "BoolFunction::simplify is unimplemented." << std::endl;
}

BoolFunction BoolFunction::operator*(const BoolFunction& other) {
  if(this->contains(other)) {
    return *this;
  }
  if(other.contains(*this)) {
    return other;
  }

  for(auto& statement: other.statements) {
    for(auto& self: this->statements) {
      for(auto& atom: statement.atoms) {
        if(!self.contains(atom)) {
          self.atoms.push_back(atom);
        }
      }
      std::sort(self.atoms.begin(), self.atoms.end());
    }
  }

  return *this;
}

bool BoolFunction::contains(const BoolFunction& other) const {
  for(auto& statement: other.statements) {
    bool found = false;
    for(auto& self: this->statements) {
      if(self.contains(statement)) {
        found = true;
        break;
      }
    }

    if(!found) {
      return false;
    }
  }

  return true;
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

bool Statement::contains(const Statement& other) const {
  for(auto& atom: other.atoms) {
    bool found = false;
    for(auto& self: this->atoms) {
      if(self == atom) {
        found = true;
        break;
      }
    }
    if(!found) {
      return false;
    }
  }

  return true;
}

bool Statement::contains(const Atom& other) const {
  for(auto& atom: this->atoms) {
    if(atom == other) {
      return true;
    }
  }
  return false;
}

Atom::Atom(int variable, bool true_or_false) {
  this->true_or_false = true_or_false;
  this->variable = variable;
}

bool Atom::operator==(const Atom& other) const {
  return this->true_or_false == other.true_or_false && this->variable == other.variable;
}

std::ostream& operator<<(std::ostream& os, const Atom& self) {
  if(self.true_or_false == false) {
    os << "~";
  }
  os << "X" << self.variable;
  return os;
}

bool Atom::operator<(const Atom& other) const {
  return this->variable < other.variable ||
    this->variable == other.variable && this->true_or_false == true;
}

Node* BoolFunction::convertToNode() const {
  Node* ret = nullptr;
  Node* one = Node::makeTerminal(1);

  if(this->statements.size() == 0) {
    return ret;
  }

  for(auto& statement: this->statements) {
    Node* cur = ret;
    bool true_or_false = false;
    bool first = true;

    for(auto& atom: statement.atoms) {
      if(ret == nullptr) {
        ret = Node::makeVariable(atom.variable);
        cur = ret;
        true_or_false = atom.true_or_false;
        first = false;
      } else {
        if(first == true) {
          true_or_false = atom.true_or_false;
          first = false;
          continue;
        }
        if(true_or_false == true) {
          if(cur->one == nullptr) {
            cur->one = Node::makeVariable(atom.variable);
          }
          cur = cur->one;
        } else {
          if(cur->zero == nullptr) {
            cur->zero = Node::makeVariable(atom.variable);
          }
          cur = cur->zero;
        }
        true_or_false = atom.true_or_false;
      }
    }

    if(true_or_false == true) {
      cur->one = one;
    } else {
      cur->zero = one;
    }
  }

  return ret;
}