#include "al/core.hpp"
using namespace al;

struct MyApp : App {
  double position = 1.1;         // mass
  double velocity = 0;           // mass
  double springStiffness = 100;  // spring
  double restPosition = 0.8;     // spring
  double timeStep = 0.01;        // simulation
  double dampingFactor = 0.05;   // environment, atmosphere

  void onCreate() override {
    // set up the system
  }

  void onAnimate(double dt) override {
    // simulation or animation; change the world/system

    // velocity is the sum of acceleration (F = ma)
    velocity += (restPosition - position) * springStiffness * timeStep;

    // damping factor
    velocity += -velocity * dampingFactor * timeStep;

    // position is the sum of velocity
    position += velocity * timeStep;
  }

  void onDraw(Graphics& g) override {
    g.clear(0.25);
    g.camera(Viewpoint::ORTHO_FOR_2D);
    g.translate(width() / 2, height() / 2);
    //
    Mesh m{Mesh::LINES};
    m.vertex(0, 0);
    m.vertex(position * width() / 3, 0);
    g.color(1);
    g.draw(m);
  }
};

int main() {
  MyApp app;
  app.initAudio();
  app.start();
}
