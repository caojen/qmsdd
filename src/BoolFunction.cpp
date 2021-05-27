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
    os << " ";
    for(int i = 0; i < self.count.size(); i++) {
      os << "[";
      os << self.count[i] << ",{";
      for(auto s: self.variables[i]) {
        os << "X" << s << ",";
      }
      os << "}]";
    }
  }

  return os;
}

void init_from_node_help(Node* root, Statement statement, BoolFunction* bf) {
  if(root->isTerminal()) {
    bf->append(statement);
  } else {
    if(bf->variables.size() == 0) {
      std::set<int> s;
      s.insert(root->variable);
      bf->variables.push_back(s);
    } else {
      bf->variables[0].insert(root->variable);
    }

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
  bf->count.push_back(bf->variables[0].size());
  // std::cout << "create bf: " << *bf << std::endl;
  return bf;
}

void BoolFunction::simplify() {
  std::cout << "BoolFunction::simplify is unimplemented." << std::endl;
}

BoolFunction BoolFunction::bf_and(const BoolFunction& other) {
  BoolFunction ret;
  if(this->contains(other)) {
    ret = *this;
    ret.count = std::vector<int>();
    ret.variables = std::vector<std::set<int>>();
  } else if(other.contains(*this)) {
    ret = other;
    ret.count = std::vector<int>();
    ret.variables = std::vector<std::set<int>>();
  } else {
    for(auto other_statement: other.statements) {
      for(auto self_statement: this->statements) {
        for(auto other_statement_atom: other_statement.atoms) {
          if(!self_statement.contains(other_statement_atom)) {
            self_statement.atoms.push_back(other_statement_atom);
          }
        }
        std::sort(self_statement.atoms.begin(), self_statement.atoms.end());
        ret.statements.push_back(self_statement);
      }
    }
  }
  for(int i = 0; i < other.count.size(); i++) {
    if(other.count[i] > 1) {
      // not exists then push
      bool exists = false;
      for(int j = 0; j < ret.variables.size(); j++) {
        if(other.variables[i] == ret.variables[j]) {
          exists = true;
          break;
        }
      }
      if(!exists) {
        ret.count.push_back(other.count[i]);
        ret.variables.push_back(other.variables[i]);
      }
    }
  }

  for(int i = 0; i < this->count.size(); i++) {
    if(this->count[i] > 1) {
      // not exists then push
      bool exists = false;
      for(int j = 0; j < ret.variables.size(); j++) {
        if(this->variables[i] == ret.variables[j]) {
          exists = true;
          break;
        }
      }
      if(!exists) {
        ret.count.push_back(this->count[i]);
        ret.variables.push_back(this->variables[i]);
      }
    }
  }
  return ret;
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
  Node* one = Node::makePrefix(this->count, this->variables, 1);

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

void BoolFunction::fix(std::vector<BoolFunction*>& bfs) {
  int size = bfs.size();

  std::set<BoolFunction*> should_remove_bfs_item;

  for(int i = 0; i < size; i++) {
    BoolFunction* bf = bfs[i];
    if(bf->count[0] == 1) {
      continue;
    }

    for(int j = 0; j < size; j++) {
      if(i == j) {
        continue;
      }

      if(bfs[j]->count[0] == 1) {
        std::set<int> should_remove;
        for(auto x: bfs[j]->variables[0]) {
          for(auto y: bf->variables[0]) {
            if(x == y) {
              should_remove_bfs_item.insert(bfs[j]);
              should_remove.insert(x);
            }
          }
        }

        for(auto x: should_remove) {
          auto it = bf->variables[0].find(x);
          bf->variables[0].erase(it);
        }
      }
    }

  }
  for(auto s: should_remove_bfs_item) {
    for(auto it = bfs.begin(); it != bfs.end(); ++it) {
      if(*it == s) {
        bfs.erase(it);
        break;
      }
    }
  }
}

void BoolFunction::remove(BoolFunction* bf) {
  std::set<int> should_remove;
  int size = bf->count.size();
  for(int i = 0; i < size; i++) {
    if(bf->count[i] == 1) {
      should_remove.insert(i);
    }
  }

  std::vector<int> count;
  std::vector<std::set<int>> variables;

  for(int i = 0; i < size; i++) {
    if(should_remove.find(i) == should_remove.end()) {
      count.push_back(bf->count[i]);
      variables.push_back(bf->variables[i]);
    }
  }

  bf->count = count;
  bf->variables = variables;
}
