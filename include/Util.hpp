#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "Node.hpp"
#include "Complex.hpp"

void insert_terminal(Node* root, int path, Complex terminal, int n);
void simplify(Node*& root);
Node* combine(std::vector<Node*>& roots);
void print_graph(Node* root, std::string prefix);
