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
  Texture pointTexture;
  Mesh point;

  void onCreate() override {
    pointShader.compile(slurp("../cross-vertex.glsl"),
                        slurp("../cross-fragment.glsl"),
                        slurp("../cross-geometry.glsl"));
    point.primitive(Mesh::POINTS);
    auto r = [](float f = 1) {
      return Vec3f(rnd::uniformS(), rnd::uniformS(), rnd::uniformS()) * f;
    };
    for (int i = 0; i < 6666; i++) {
      point.vertex(r(5));
    }
  }

  double angle{0};
  void onAnimate(double dt) override {
    //
    angle += 0.1;
  }

  void onDraw(Graphics& g) override {
    g.clear(0.23);
    g.rotate(angle, 0, 1, 0);
    g.shader(pointShader);
    g.shader().uniform("shape", 0.03, 0.003);
    g.draw(point);
    g.shader().uniform("shape", 0.003, 0.03);
    g.draw(point);
  }
};

int main() { AlloApp().start(); }