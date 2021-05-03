#include "Util.hpp"

void insert_terminal(Node* root, int path, Complex terminal, int n) {
  if(n == 1) {
    int p = path & 1;
    Node* t = Node::makeTerminal(terminal);
    t->parent = root;
    if(p == 0) {
      root->zero = t;
    } else {
      root->one = t;
    }

    return;
  }

  int p = (path >> (n-1)) & 1;
  Node* t = nullptr;
  if(p == 0) {
    t = root->zero;
  } else {
    t = root->one;
  }
  if(t == nullptr) {
    t = Node::makeVariable(root->variable + 1);
    t->parent = root;
    if(p == 0) {
      root->zero = t;
    } else {
      root->one = t;
    }
  }

  insert_terminal(t, path, terminal, n - 1);
}

void simplify(Node*& root) {

}

Node* combine(Node* ret, Node* root) {
  return nullptr;
}

void print_graph(Node* root, std::string prefix) {
  if(root->isTerminal()) {
    std::cout << prefix << ": " << root->terminal << std::endl;
  } else {
    prefix += root->variable + '0';
    if(root->zero) {
      print_graph(root->zero, prefix + "1");
    }
    if(root->one) {
      print_graph(root->one, prefix + "0");
    }
  }
}