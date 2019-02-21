#include "al/core.hpp"
using namespace al;

struct AnimationProcess {
  double start{0};
  double stop{1};
  double t{0};  // (0, 1)

  float map(float value, float low, float high, float Low, float High) {
    return Low + (High - Low) * ((value - low) / (high - low));
  }

  bool operator()(double time) { return active(time); }
  bool active(double time) {
    t = map(time, start, stop, 0, 1);
    return time > start && time < stop;
  }

  bool done(double time) {
    //
    return time > stop;
  }

  void schedule(double start, double stop) {
    this->start = start;
    this->stop = stop;
    t = 0;
  }
};

struct MeshAnimation : AnimationProcess {
  Mesh mesh;
};

struct MyApp : App {
  MeshAnimation vertical;
  MeshAnimation horizontal;

  void onCreate() override {
    vertical.schedule(1, 7);
    vertical.mesh.primitive(Mesh::LINES);
    vertical.mesh.vertex(0, 0);
    vertical.mesh.vertex(0, height());

    horizontal.schedule(2, 5);
    horizontal.mesh.primitive(Mesh::LINES);
    horizontal.mesh.vertex(0, 0);
    horizontal.mesh.vertex(width(), 0);
  }

  void onDraw(Graphics& g) override {
    g.clear(0.15);
    g.camera(Viewpoint::ORTHO_FOR_2D);
    g.color(1);

    if (vertical(time)) {
      g.draw(vertical.mesh);
    }

    if (horizontal(time)) {
      g.draw(horizontal.mesh);
    }
  }

  double time = 0;
  void onAnimate(double dt) override {
    time += dt;

    if (vertical(time)) {
      vertical.mesh.vertices()[0].x = (0.1 + 0.8 * vertical.t) * width();
      vertical.mesh.vertices()[1].x = (0.1 + 0.8 * vertical.t) * width();
      vertical.mesh.vertices()[0].y = 0;
      vertical.mesh.vertices()[1].y = height();
    }

    if (vertical.done(time)) {
      //
      vertical.schedule(2 + time, 7 + time);
    }

    if (horizontal(time)) {
      horizontal.mesh.vertices()[0].y = (0.1 + 0.8 * horizontal.t) * height();
      horizontal.mesh.vertices()[1].y = (0.1 + 0.8 * horizontal.t) * height();
      horizontal.mesh.vertices()[0].x = 0;
      horizontal.mesh.vertices()[1].x = width();
    }

    if (horizontal.done(time)) {
      //
      horizontal.schedule(1 + time, 5 + time);
    }
  }
};

int main() {
  MyApp app;
  app.initAudio();
  app.start();
}
