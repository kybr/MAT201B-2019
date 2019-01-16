#include "al/core.hpp"
using namespace al;

float map(float value, float low, float high, float Low, float High) {
  return Low + (High - Low) * ((value - low) / (high - low));
}

struct MyApp : App {
  // a Mesh is a...
  // - collection of points (vertices)
  // - a way to draw them (called a primitive)
  Mesh points;

  float mouseX, mouseY;

  // onMouseMove is like mouseMoved() in Processing
  void onMouseMove(Mouse const& m) override {
    mouseX = m.x();
    mouseY = m.y();
  }

  // onCreate is like "setup" from Processing
  void onCreate() override {
    //
    points.primitive(Mesh::LINE_STRIP);
  }

  // Processing does not have anything like onAnimate
  // onAnimate is called just before onDraw
  void onAnimate(double dt) override {
    points.reset();
    points.vertex(width() / 2, height() / 2);
    points.color(0, 1, 1);
    points.vertex(mouseX, height() - mouseY);
    points.color(1, 1, 0);
  }

  // onDraw is like "draw" from Processing
  void onDraw(Graphics& g) override {
    g.clear(0.25);  // background(64);

    // (0, 0) is the lower left corner
    // (width, height) is the upper right corner in pixels
    g.camera(Viewpoint::ORTHO_FOR_2D);

    g.meshColor();
    g.draw(points);  // send to GPU+screen
  }
};

int main() {
  MyApp app;
  app.start();
}
