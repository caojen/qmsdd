#pragma once

#include "Node.hpp"

class SDD {
  Node* graph;

public:
  SDD(Node* graph);
  int count() const;
};