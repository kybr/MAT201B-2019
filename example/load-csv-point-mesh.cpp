// .csv loader
// expects: float,float,float
// see regex below

#include <fstream>
#include <iostream>
#include <regex>
#include <string>
using namespace std;

struct Point {
  float x, y, z;
};
vector<Point> point;

int main(int argc, char* argv[]) {
  string fileName = "../float-data.csv";
  if (argc > 1) fileName = argv[1];  // use command line argument

  fstream file(fileName);

  while (file.good()) {
    string line;
    getline(file, line);
    regex xyz_float(R"|(\s*(\S+)\s*,\s*(\S+)\s*,\s*(\S+)\s*)|");
    auto begin = sregex_iterator(line.begin(), line.end(), xyz_float);
    auto end = sregex_iterator();
    for (auto p = begin; p != end; ++p) {
      point.push_back({stof((*p)[1]), stof((*p)[2]), stof((*p)[3])});
    }
  }

  for (auto& p : point) {
    cout << p.x << " " << p.y << " " << p.z << endl;
  }
}
