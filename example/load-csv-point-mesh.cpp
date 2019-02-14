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
    for (sregex_iterator i = begin; i != end; ++i) {
      smatch match = *i;
      point.push_back({stof(match[1]), stof(match[2]), stof(match[3])});
    }
  }

  for (auto& p : point) {
    cout << p.x << " " << p.y << " " << p.z << endl;
  }
}
