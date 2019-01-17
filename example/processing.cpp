#include "al/core.hpp"
using namespace al;

#include "synths.h"
using namespace diy;

#include "processing.h"
using namespace processing;

struct MyApp : App {
  void onCreate() override {
    //
  }

  void onAnimate(double dt) override {
    //
  }

  void onDraw(Graphics& g) override {
    g.clear(0.25);
    g.camera(Viewpoint::ORTHO_FOR_2D);

    initialize(g);
    noStroke();
    fill(0.5, 0, 0);
    ellipse(200, 200, 100, 100);
    fill(0.5);
    stroke(0, 1, 1);
    rect(400, 400, 50, 200);
    stroke(1, 1, 0);
    line(width() / 2, height() / 2, mouseX, mouseY);
  }

  float mouseX, mouseY;
  void onMouseMove(Mouse const& m) override {
    mouseX = m.x();
    mouseY = height() - m.y();
  }
};

int main() {
  MyApp app;
  app.start();
}
