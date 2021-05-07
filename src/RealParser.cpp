#include "RealParser.hpp"
#include "Util.hpp"

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

  std::vector<Node*> ret;
  for(auto& edge: edges) {
    Node* node = qmdd_to_qmsdd_node(edge);
    // std::cout << "'" << std::endl;
    // print_graph(edge, "");
    ret.push_back(node);
  }

  // for(int i = 0; i < ret.size(); i++) {
  //   print_graph(ret[i], std::to_string(i) + ": ");
  // }
  return ret;
}