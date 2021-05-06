#include <iostream>
#include <fstream>
#include <chrono>

#include "Node.hpp"

void input_table(char* filename) {
  std::fstream fstream(filename);
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

  auto start_time = std::chrono::steady_clock::now();
  Node* graph = Node::initWithTable(table, fn, c, n);
  auto end_time = std::chrono::steady_clock::now();
  std::chrono::duration<double, std::micro> elapsed = end_time - start_time;
  int size = graph->countNodes();
  std::cout << "Done.. Final Size = " << size << std::endl;
  std::cout << "Total Time = " << elapsed.count() << "us" << std::endl;
}

int main(int argc, char** argv) {
  if(argc <= 1) {
    std::cout << "Please provide test file." << std::endl;
    return 1;
  }

  char* filename = argv[1];
  std::cout << "Detected File: " << filename << std::endl;
  if(strlen(filename) < 5 || std::string(filename + strlen(filename) - 5) == "table") {
    // *.table file
    input_table(filename);
  } else {
    // *.real file
  }
}