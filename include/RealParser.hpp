#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>

#include "Node.hpp"

class RealParser {
  std::string filename;
  std::map<std::string, int> variable_map;
public:
  RealParser(const std::string& filename);
  Node* parse() const;
};