#include "al/core.hpp"
#include "al/core/math/al_Random.hpp"
using namespace al;

#include <vector>
using namespace std;

void circle(Graphics& g, Vec2f center, float radius) {
  Mesh m{Mesh::TRIANGLE_FAN};
  m.vertex(center);
  for (int i = 0; i < 101; ++i)
    m.vertex(center.x + radius * sin(M_2PI * i / 100),
             center.y + radius * cos(M_2PI * i / 100));
  g.color(1);
  g.draw(m);
}

// draw a line, given two points, a and b
void line(Graphics& g, Vec2f a, Vec2f b) {
  Mesh m{Mesh::LINES};
  m.vertex(a);
  m.vertex(b);
  g.color(1);
  g.draw(m);
}

struct Mass : Vec2f {
  Vec2f velocity;
  float mass;
};

struct MyApp : App {
  // simulation parameters
  double timeStep = 0.005;
  double dragFactor = 0.01;
  rnd::Random<> rng;

  MyApp() {
    //
  }

  vector<Mass> mass;

  void reset() {
    mass.clear();
    // mass.resize(4, Mass{});
    // mass[0].set(-0.5, 0);
    // mass[0].mass = 0.11;
    // mass[1].set(1, 0);
    // mass[1].mass = 0.19;
    // mass[2].set(1, 1);
    // mass[2].mass = 0.27;
    // mass[3].set(0, 1.1);
    // mass[3].mass = 0.17;

    rng.seed(0);

    for (int i = 0; i < 10; ++i) {
      mass.emplace_back();
      mass.back().set(Vec2f(rng.uniformS(), rng.uniformS()) * 2);
      mass.back().mass = rng.uniform(0.7, 0.1);
    }
    for (auto& m : mass) m.velocity = Vec2f(rng.uniformS(), rng.uniformS()) * 2;
  }

  void onCreate() override {
    //
    reset();
  }

  float gravitationalConstant = 100;  // why???

  // float maximum = 0;

  bool paused = false;
  void onAnimate(double dt) override {
    if (paused) return;

    // calculates forces between pairs of particles
    // integrates those forces into mass velocities
    for (int i = 0; i < mass.size(); ++i)
      for (int j = 1 + i; j < mass.size(); ++j) {
        Vec2f difference = mass[j] - mass[i];  // B - A
        float distance = difference.mag();
        Vec2f force = difference * gravitationalConstant /
                      (distance * distance * distance);

        // find the maximum
        // if (force.mag() > maximum) {
        //   maximum = force.mag();
        //   cout << maximum << endl;
        // }

        // limit large forces
        if (force.mag() > 4000) force.normalize(4000);

        mass[i].velocity += force * mass[j].mass * timeStep;
        mass[j].velocity -= force * mass[i].mass * timeStep;
      }

    // add drag
    for (Mass& m : mass) {
      m.velocity += -m.velocity * dragFactor * timeStep;
    }

    // integrate velocity
    for (Mass& m : mass) {
      m += m.velocity * timeStep;
    }
  }

  float scale = 0.1;
  void onDraw(Graphics& g) override {
    g.clear(0.25);
    g.camera(Viewpoint::IDENTITY);
    g.scale((float)height() / width(), 1, 1);
    g.scale(scale);

    for (Mass& m : mass) {
      circle(g, m, m.mass);
    }
  }

  void onKeyDown(const Keyboard& k) {
    switch (k.key()) {
      case 'r':
        reset();
        break;

      case 'p':
        paused = !paused;  // toggle
        break;

      case 'w':
        if (scale < 1) scale += 0.01;
        break;
      case 'x':
        if (scale > 0.01) scale -= 0.01;
        break;

      case Keyboard::UP:
        timeStep *= 1.1;
        break;
      case Keyboard::DOWN:
        timeStep /= 1.1;
        break;

      case Keyboard::LEFT:
        if (timeStep > 0) timeStep *= -1;
        break;
      case Keyboard::RIGHT:
        if (timeStep < 0) timeStep *= -1;
        break;
    }
    //
  }
};

int main() {
  MyApp app;
  app.initAudio();
  app.start();
}