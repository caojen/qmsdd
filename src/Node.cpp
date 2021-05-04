#include <set>

#include "Node.hpp"
#include "Util.hpp"

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

int Node::countNodes() const {
  return 0;
}

Node* Node::initWithTable(char** table, int x, int y, int n) {
  std::vector<Node*> roots;
  for(int line = 0; line < x; line++) {
    Node* root = Node::makeVariable(1);
    for(int col = 0; col < y; col++) {
      if(table[line][col] >= '0' && table[line][col] <= '9') {
        insert_terminal(root, col, (int)(table[line][col] - '0'), n);
      } else {
        insert_terminal(root, col, table[line][col], n);
      }
    }
    simplify(root);
    if(root->isTerminal()) {
      std::cout << "#" << line + 1 << " is TRUE. Ignored..." << std::endl;
      continue;
    }
    print_graph(root, std::string("#") + (char)(line + 1 + '0') + std::string(" "));
    std::cout << "count nodes = " << root->countNodes() << std::endl;
    roots.push_back(root);
  }
  return combine(roots);
}

bool Node::operator==(const Node& other) const {
  if(this == &other) {
    return true;
  }

  bool this_is_terminal = this->isTerminal();
  bool other_is_terminal = other.isTerminal();

  if(this_is_terminal != other_is_terminal) {
    return false;
  }

  if(this_is_terminal) {
    return this->terminal == other.terminal;
  } else {
    if(this->variable != other.variable) {
      return false;
    } else {
      if(this->zero == nullptr) {
        if(other.zero != nullptr) {
          return false;
        }
      } else {
        if(other.zero == nullptr) {
          return false;
        } else {
          if((*this->zero == *other.zero) == false) {
            return false;
          }
        }
      }

      if(this->one == nullptr) {
        if(other.one != nullptr) {
          return false;
        }
      } else {
        if(other.one == nullptr) {
          return false;
        } else {
          if((*this->one == *other.one) == false) {
            return false;
          }
        }
      }
      return true;
    }
  }
}