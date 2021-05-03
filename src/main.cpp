#include <iostream>
#include <fstream>

#include "Node.hpp"

int main(int argc, char** argv) {
  if(argc <= 1) {
    std::cout << "Please provide test file." << std::endl;
    return 1;
  }

  char* filename = argv[1];
  std::fstream fstream(filename);
  std::cout << "Detected File: " << filename << std::endl;
  int n;
  int fn;
  fstream >> n >> fn;
  std::cout << "Variable Max Count: " << n << std::endl;
  std::cout << "Function Count: " << fn << std::endl;

  int c = 1 << n;

  char** table = new char*[fn];
  for(int i = 0; i < fn; i++) {
    table[i] = new char[c];
  }

  for(int f = 0; f < fn; f++) {
    for(int y = 0; y < c; y++) {
      fstream >> table[f][y];
    }
  }

  std::cout << "Receive Table: " << fn << "*" << c << std::endl;
  for(int f = 0; f < fn; f++) {
    for(int y = 0; y < c; y++) {
      std::cout << table[f][y] << ' ';
    }
    std::cout << std::endl;
  }

  Node* graph = Node::initWithTable(table, fn, c, n);

  return 0;
}