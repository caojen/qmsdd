#include "RealParser.hpp"

RealParser::RealParser(const std::string& filename) {
  this->filename = filename;
}

Node* RealParser::parse() {
  QMDDrevlibDescription c;
  std::vector<QMDDedge> edges;
  char* fname = new char[this->filename.size() + 1];
  strcpy(fname, this->filename.c_str());
  QMDDcircuitRevlib(fname, c, 0, &edges);
  delete[] fname;
  return nullptr;
}