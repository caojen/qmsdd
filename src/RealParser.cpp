#include "RealParser.hpp"

RealParser::RealParser(const std::string& filename) {
  this->filename = filename;

  std::fstream fstream(filename);
  if(!fstream.is_open()) {
    std::cout << "no such file: " << filename << std::endl;
    exit(1);
  }
}

Node* RealParser::parse() const {
  return nullptr;
}