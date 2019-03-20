#include "al/core.hpp"
using namespace al;

#include <fstream>
#include <vector>
using namespace std;

string slurp(string fileName) {
  fstream file(fileName);
  string returnValue = "";
  while (file.good()) {
    string line;
    getline(file, line);
    returnValue += line + "\n";
  }
  return returnValue;
}

struct AlloApp : App {
  ShaderProgram pointShader;
  ShaderProgram lineShader;
  Mesh dashed;

  void onCreate() override {
    lineShader.compile(slurp("../line-vertex.glsl"),
                       slurp("../line-fragment.glsl"),
                       slurp("../line-geometry.glsl"));
    dashed.primitive(Mesh::LINES);

    for (int z = 0; z < 10; z++) {
      for (int i = 0; i < 2000; i++) {
        dashed.vertex(
            (i - 1000) / 100.0,
            sin(sqrt(z) * 0.1 * (i - 1000)) / (0.1 * (i - 1000) / sqrt(z)),
            (z - 5));
      }
    }

    nav().pos(0, 5, 17);
    nav().faceToward(Vec3d(0, 0, 0));
  }

  double angle{0};

  void onAnimate(double dt) override { angle += 0.1; }

  void onDraw(Graphics& g) override {
    g.clear(0.23);
    g.rotate(angle, 0, 1, 0);
    g.shader(lineShader);
    g.shader().uniform("strokeWeight", 0.007 + 0.006 * sin(angle));
    dashed.primitive(Mesh::LINES);
    g.draw(dashed);
  }
};

int main() { AlloApp().start(); }