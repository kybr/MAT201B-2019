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

    auto sinc = [](float f) {
      if (f == 0) return 1.0f;
      return sinf(f) / f;
    };

#if 0
    for (int z = -20; z < 20; z++) {
      Vec3f _(-2000 / 100.0,
              2 * sinc(0.007 * sqrt(abs(z)) * -2000) / sqrt(abs(z)), z);
      for (int i = -1999; i < 2000; i++) {
        float f = sqrt(abs(z));
        Vec3f v(i / 100.0, 2 * sinc(0.007 * f * i) / f, z);
        dashed.vertex(_);
        dashed.vertex(v);
        _ = v;
      }
    }
#else
    for (int z = -20; z < 20; z++) {
      for (int i = -2000; i < 2000; i++) {
        float f = sqrt(abs(z));
        Vec3f v(i / 100.0, 2 * sinc(0.007 * f * i) / f, z);
        dashed.vertex(v);
      }
    }
#endif

    nav().pos(0, 5, 17);
    nav().faceToward(Vec3d(0, 0, 0));

    nav().pos(Vec3d(-17.100191, 1.498830, 8.387591));
    nav().quat(Quatd(0.905471, -0.125915, -0.403678, -0.036204));
  }

  void onDraw(Graphics& g) override {
    g.clear(0.23);
    g.shader(lineShader);
    g.shader().uniform("strokeWeight", 0.003);
    g.shader().uniform("al_EyePosition", nav().pos());
    dashed.primitive(Mesh::LINES);
    g.draw(dashed);
  }
};

int main() { AlloApp().start(); }