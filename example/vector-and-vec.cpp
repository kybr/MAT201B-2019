#include "al/core.hpp"
using namespace al;

#include <vector>
using namespace std;

int main() {
  Vec3f v;  // defined by allolib and used a LOT
  Vec3f up(0, 1, 0);

  v.x = 1;
  v.y += 0.1;
  v.y += 0.1;
  v.y += 0.1;

  up.dot(v);                 // the dot product from linear algebra
  Vec3f out = cross(up, v);  // cross product from linear algebra

  Mesh mesh;
  mesh.primitive(Mesh::TRIANGLES);
  mesh.vertex(0, 0, 0);  // vertex 0
  mesh.vertex(0, 1, 0);  // vertex 1
  mesh.vertex(1, 0, 0);  // vertex 2
  auto& verts = mesh.vertices();
  cout << verts[1].y << endl;

  // std::vector is different than Vec3f
  // std::vector is defined by the c++ standard library
  vector<float> floatList;  // these are arrays, but better
  floatList.push_back(3.3);

  for (int i = 0; i < 10; ++i) floatList.push_back(rnd::uniform(1.0));

  for (auto f : floatList)  // a "range" for loop
    cout << f << endl;

  cout << "the size is " << floatList.size() << endl;
}
