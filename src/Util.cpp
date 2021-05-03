#include <queue>
#include <stack>
#include <string>

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
  Node* one = Node::makeTerminal(1);

  // get all nodes
  std::queue<Node*> queue;
  std::stack<Node*> stack;
  queue.push(root);
  while(queue.empty() == false) {
    Node* node = queue.front(); queue.pop();
    stack.push(node);

    if(!node->zero->isTerminal()) {
      queue.push(node->zero);
    } else if(node->zero->terminal == 0) {
      node->zero = nullptr;
    } else {
      node->zero = one;
    }
    if(!node->one->isTerminal()) {
      queue.push(node->one);
    } else if(node->one->terminal == 0) {
      node->one = nullptr;
    } else {
      node->one = one;
    }
  }

  while(stack.size()) {
    Node* node = stack.top(); stack.pop();
    if(node->one == nullptr && node->zero != nullptr || node->one != nullptr && node->zero == nullptr) {
      continue;
    } else if(node->one == nullptr && node->zero == nullptr) {
      Node* parent = node->parent;
      if(parent == nullptr) {
        root = nullptr; // the root
      } else {
        if(parent->one == node) {
          parent->one = nullptr;
        } else {
          parent->zero = nullptr;
        }
      }
      continue;
    }
    if(*node->one == *node->zero) {
      Node* parent = node->parent;
      if(parent == nullptr) { // the root
        root = node->one;
      } else {
        if(parent->one == node) {
          parent->one = node->one;
        } else {
          parent->zero = node->one;
        }
      }
    }
  }
}

Node* combine(Node* ret, Node* root) {
  return nullptr;
}

void print_graph(Node* root, std::string prefix = "") {
  if(root->isTerminal()) {
    std::cout << prefix << ": " << root->terminal << std::endl;
  } else {
    prefix += root->variable + '0';
    if(root->zero) {
      print_graph(root->zero, prefix + "0");
    }
    if(root->one) {
      print_graph(root->one, prefix + "1");
    }
  }
}