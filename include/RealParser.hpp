#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>

#include "Node.hpp"
#include "QMDDpackage.h"
#include "QMDDcircuit.h"

class RealParser {
  std::string filename;
  std::map<std::string, int> variable_map;
public:
  RealParser(const std::string& filename);
  std::vector<Node*> parse();
};
