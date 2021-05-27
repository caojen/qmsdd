#include <queue>
#include <stack>
#include <string>
#include <map>
#include <set>

#include "Util.hpp"
#include "BoolFunction.hpp"

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

void simplify(Node*& root, Node* terminal) {
  Node* one;
  if(terminal == nullptr) {
    one = Node::makeTerminal(1);
  } else {
    one = terminal; 
  }

  // get all nodes
  std::queue<Node*> queue;
  std::stack<Node*> stack;
  queue.push(root);
  while(queue.empty() == false) {
    Node* node = queue.front(); queue.pop();
    stack.push(node);

    if(node->zero != nullptr) {
      if(!node->zero->isTerminal()) {
        queue.push(node->zero);
      } else if(node->zero->terminal == 0) {
        node->zero = nullptr;
      } else {
        node->zero = one;
      }
    }
    if(node->one != nullptr) {
      if(!node->one->isTerminal()) {
        queue.push(node->one);
      } else if(node->one->terminal == 0) {
        node->one = nullptr;
      } else {
        node->one = one;
      }
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

  // map: level -> level's nodes
  std::map<Node*, std::set<Node*>> nodes;
  queue.push(root);
  while(!queue.empty()) {
    Node* node = queue.front(); queue.pop();
    if(node == nullptr || node->isTerminal()) {
      continue;
    }

    if(node->one != nullptr && node->one->isTerminal() == false) {
      queue.push(node->one);
      nodes[node->one].insert(node);
    }
    if(node->zero != nullptr && node->zero->isTerminal() == false) {
      queue.push(node->zero);
      nodes[node->zero].insert(node);
    }
  }

  for(auto itx = nodes.begin(); itx != nodes.end(); ++itx) {
    for(auto ity = itx; ity != nodes.end(); ++ity) {
      if(itx->first == ity->first) {
        continue;
      }
      if(*itx->first == *ity->first) {
        for(auto& parent: ity->second) {
          if(parent->one == ity->first) {
            parent->one = itx->first;
          } else if(parent->zero == ity->first) {
            parent->zero = itx->first;
          }
        }
      }
    }
  }
}

Node* combine(std::vector<Node*>& roots) {
  if(roots.size() == 0) {
    return nullptr;
  } else if(roots.size() == 1) {
    return roots[0];
  }
  
  std::vector<BoolFunction*> bfs;
  std::vector<int> nodeCounts;
  for(auto& root: roots) {
    auto bf = BoolFunction::initFromNode(root);
    bfs.push_back(bf);
    int count = root->countNodes();
    nodeCounts.push_back(count);
  }

  BoolFunction::fix(bfs);

  BoolFunction* ret = bfs[0];
  // std::cout << "init ret(bfs[0]) = " << *ret << std::endl;
  int size = bfs.size();
  for(int i = 1; i < size; i++) {
    // std::cout << "next bfs" << i << " " << *bfs[i] << std::endl;
    *ret = ret->bf_and(*bfs[i]);
    // std::cout << "merge to " << *ret << std::endl;
  }

  // std::cout << "merge all bf done: " << *ret << std::endl;
  BoolFunction::remove(ret);
  // std::cout << "after fix: " << *ret << std::endl;
  Node* r = ret->convertToNode();
  // print_graph(r, "after merge: ");
  Node* terminal = Node::findTerminal(r);
  simplify(r, terminal);
  // print_graph(r, "after simplify: ");
  return r;
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

void print_graph(QMDDedge& edge, std::string prefix = "") {
  prefix += "(weight " + std::to_string(edge.w) + ")";
  QMDDnode* node = edge.p;
  if(node == nullptr || node->v == 255) {
    std::cout << prefix << " -> T" << std::endl;;
  } else {
    prefix += " " + std::to_string(node->v) + " "; 
    for(int i = 0; i < 4; i++) {
      print_graph(node->e[i], prefix);
    }
  }
  return;
}

Node* qmdd_to_qmsdd_node(QMDDedge& edge) {
  // std::cout << "print_graph..." << std::endl;
  // print_graph(edge);

  Node* nodeOne = Node::makeTerminal(1);

  if(edge.p == nullptr) {
    return nullptr;
  }

  Node* ret = nullptr;
  std::map<QMDDnode*, Node*> map;
  std::queue<QMDDnode*> queue;
  queue.push(edge.p);

  while(queue.empty() == false) {
    QMDDnode* qmnode = queue.front(); queue.pop();
    int variable = qmnode->v;
    Node* node = nullptr;
    if(ret == nullptr) {
      ret = Node::makeVariable(variable);
      map[qmnode] = ret;
      node = ret;
    } else {
      node = map[qmnode];
    }

    QMDDnode *one = nullptr, *zero = nullptr;
    for(int i = 0; i < 4; i++) {
      int w = qmnode->e[i].w;
      if(w >= COMPLEXTSIZE) {
        // something went wrong from qmddpackage
        continue;
      }
      complex c = Cvalue(w);
      if(c.r == 0 && c.i == 0) {
        zero = qmnode->e[i].p;
      } else {
        one = qmnode->e[i].p;
      }
    }

    if(zero != nullptr && zero->v != 255) {
      queue.push(zero);
      node->zero = Node::makeVariable(zero->v);
      map[zero] = node->zero;
    }

    if(one != nullptr && one->v != 255) {
      queue.push(one);
      node->one = Node::makeVariable(one->v);
      map[one] = node->one;
    } else {
      node->one = nodeOne;
    }
  }

  // print_graph(ret);
  return ret;
}