#include "sdd.hpp"
#include "BoolFunction.hpp"

SDD::SDD(Node* graph) {
  this->graph = graph;
}

int SDD::count() const {
  BoolFunction* bf = BoolFunction::initFromNode(this->graph);
  int count = 0;
  for(auto& statement: bf->statements) {
    for(auto& atom: statement.atoms) {
      count++;
    }
  }

  double t = count * 0.5;
  int res = 1;
  if(t != (int)t) {
    res += (int) t + 1;
  } else {
    res += (int) t;
  }

  return res;
}