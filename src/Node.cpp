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
  Node* ret = nullptr;
  for(int line = 0; line < x; line++) {
    Node* root = Node::makeVariable(1);
    for(int col = 0; col < y; col++) {
      if(table[line][col] >= '0' && table[line][col] <= '9') {
        insert_terminal(root, col, (int)(table[line][col] - '0'), n);
      } else {
        insert_terminal(root, col, table[line][col], n);
      }
    }
    print_graph(root);
    simplify(root);

    if(!root->isTerminal()) {
      if(ret == nullptr) {
        ret = root;
      } else {
        ret = combine(ret, root);
      }
    }
  }
  return ret;
}