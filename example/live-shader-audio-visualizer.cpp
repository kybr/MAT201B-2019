#include "al/core.hpp"
using namespace al;

#include "Gamma/SamplePlayer.h"
using namespace gam;

#include <fstream>
#include <string>
using namespace std;

const char* vertexCode = R"(
#version 400
layout (location = 0) in vec3 vertexPosition;
uniform mat4 al_ModelViewMatrix;
uniform mat4 al_ProjectionMatrix;
void main() {
  gl_Position = al_ProjectionMatrix * al_ModelViewMatrix * vec4(vertexPosition, 1.0);
}
)";

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

struct MyApp : App {
  gam::SamplePlayer<float, gam::ipl::Linear, gam::phsInc::Loop> samplePlayer;
  ShaderProgram shader;
  Texture texture;

  void onCreate() override {
    samplePlayer.load("../sound/8.wav");
    samplePlayer.loop();
    Sync::master().spu(audioIO().fps());

    string fragmentCode = slurp("../shader-fragment.glsl");
    shader.compile(vertexCode, fragmentCode);
  }

  void onDraw(Graphics& g) override {
    //
    g.clear(0.25);
    g.camera(Viewpoint::IDENTITY);

    g.shader(shader);
    g.shader().uniform("time", time);
    g.shader().uniform("window", Vec2f(width(), height()));
    g.shader().uniform("mouse", Vec2f(mouseX, mouseY));
    Mesh m{Mesh::TRIANGLE_STRIP};
    m.vertex(1, 1);
    m.vertex(1, -1);
    m.vertex(-1, 1);
    m.vertex(-1, -1);

    // g.color(1); // XXX overrides shader
    g.draw(m);

    // g.quadViewport(texture);
  }

  int mouseX, mouseY;
  void onMouseMove(const Mouse& m) {
    mouseX = m.x();
    mouseY = m.y();
  }

  void onSound(AudioIOData& io) override {
    while (io()) {
      float f = samplePlayer();
      io.out(0) = f;
      io.out(1) = f;
    }
  }

  double time = 0;
  void onAnimate(double dt) override {
    time += dt;
    //
    // check if there is a "new" version of the fragment shader
    // if so, reload, recompile
  }
};

int main() {
  MyApp app;
  app.initAudio();
  app.start();
}
