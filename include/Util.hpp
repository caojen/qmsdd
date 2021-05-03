#pragma once

#include <iostream>
#include <string>

#include "Node.hpp"
#include "Complex.hpp"

void insert_terminal(Node* root, int path, Complex terminal, int n);
void simplify(Node*& root);
Node* combine(Node* ret, Node* root);
void print_graph(Node* root, std::string prefix = "");