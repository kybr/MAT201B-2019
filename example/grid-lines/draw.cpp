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
  Mesh line;

  void onCreate() override {
    cursorHide(true);
    lineShader.compile(slurp("../line-vertex.glsl"),
                       slurp("../line-fragment.glsl"),
                       slurp("../line-geometry.glsl"));
    line.primitive(Mesh::LINES);

    int N = 200;
    int S = 10;
    for (float x = -N; x < N; x += S) {
      for (float y = -N; y < N; y += S) {
        for (float z = -N; z < N; z += S) {
          // points down the z
          line.vertex(x, y, z);
          line.vertex(x, y, z + S);

          // points down the x
          line.vertex(x, y, z);
          line.vertex(x, y + S, z);

          // points down the y
          line.vertex(x, y, z);
          line.vertex(x + S, y, z);
        }
      }
    }

    nav().pos(1, 2, 10);
    lens().far(1000);
  }

  void onDraw(Graphics& g) override {
    g.clear(0.23);
    g.blending(true);
    g.blendModeTrans();
    // g.blendModeAdd();  // saturates for a "burned in" look
    g.shader(lineShader);
    g.shader().uniform("strokeWeight", 0.05);
    g.shader().uniform("al_EyePosition", nav().pos());
    g.draw(line);
  }
};

int main() { AlloApp().start(); }