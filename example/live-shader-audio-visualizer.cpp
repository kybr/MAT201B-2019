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
    // XXX missing one step
  gl_Position = al_ModelViewMatrix * vec4(vertexPosition, 1.0);
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

  void onCreate() override {
    samplePlayer.load("../sound/8.wav");
    samplePlayer.loop();
    Sync::master().spu(audioIO().fps());

    string fragmentCode;  // comes from a file
    // slurp: file -> string
    shader.compile(vertexCode, fragmentCode);
  }

  void onSound(AudioIOData& io) override {
    while (io()) {
      float f = samplePlayer();
      io.out(0) = f;
      io.out(1) = f;
    }
  }
  void onAnimate(double dt) override {
    //
    // check if there is a "new" version of the fragment shader
    // if so, reload, recompile
  }

  void onDraw(Graphics& g) override {
    //
    g.clear(0.25);
  }
};

int main() {
  MyApp app;
  app.initAudio();
  app.start();
}
