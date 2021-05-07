#include "RealParser.hpp"

RealParser::RealParser(const std::string& filename) {
  this->filename = filename;
}

std::vector<Node*> RealParser::parse() {
  QMDDinit(0);

  QMDDrevlibDescription c;
  std::vector<QMDDedge> edges;
  char* fname = new char[this->filename.size() + 1];
  strcpy(fname, this->filename.c_str());
  QMDDcircuitRevlib(fname, c, 0, &edges);
  std::cout << "Line Count: " << edges.size() << std::endl;
  delete[] fname;
  return std::vector<Node*>();
}