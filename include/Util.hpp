#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "Node.hpp"
#include "Complex.hpp"
#include "QMDDpackage.h"

void insert_terminal(Node* root, int path, Complex terminal, int n);
void simplify(Node*& root, Node* terminal = nullptr);
Node* combine(std::vector<Node*>& roots);
void print_graph(Node* root, std::string prefix);
void print_graph(QMDDedge& edge, std::string prefix);

Node* qmdd_to_qmsdd_node(QMDDedge& edge);
