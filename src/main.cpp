#include <iostream>
#include <fstream>
#include <chrono>

#include "Node.hpp"
#include "RealParser.hpp"

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

void input_real(char* filename) {

  std::vector<std::string> excepts; // except these filename
  excepts.push_back("qFou7.real");

  std::string f(filename);
  for(auto& s: excepts) {
    if(f.find(s) != std::string::npos) {
      std::cout << "This file has been excepted..." << std::endl;
      exit(0);
    }
  }

  RealParser realParser(filename);
  realParser.parse();
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
    input_real(filename);
  }
}