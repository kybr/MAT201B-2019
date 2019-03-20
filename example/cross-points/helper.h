#ifndef __HELPER__
#define __HELPER__

#include <fstream>
#include <sstream>
#include <string>

std::string slurp(std::ifstream& in) {
  return static_cast<std::stringstream const&>(std::stringstream()
                                               << in.rdbuf())
      .str();
}

std::string slurp(std::string filePath) {
  std::ifstream in(filePath);
  return slurp(in);
}

std::string slurp(std::string& filePath) {
  std::ifstream in(filePath);
  return slurp(in);
}

void spurt(std::string& input, std::string filePath) {
  std::ofstream out(filePath);
  out << input;
  out.close();
}

#endif