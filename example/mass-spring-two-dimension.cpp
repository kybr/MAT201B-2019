#include "al/core.hpp"
using namespace al;

#include <vector>
using namespace std;

// make this 2d
// make multiple masses and springs

// 3 masses, 3 springs, in a triangle

void circle(Graphics& g, Vec2f v, float r) {
  Mesh m{Mesh::TRIANGLE_FAN};
  m.vertex(v);
  for (int i = 0; i < 101; ++i)
    m.vertex(v.x + r * sin(M_2PI * i / 100), v.y + r * cos(M_2PI * i / 100));
  g.color(1);
  g.draw(m);
}

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

struct Spring {
  Mass& a;
  Mass& b;
  float restLength, stiffness;
};

struct MyApp : App {
  double timeStep = 0.001;   // simulation
  double dragFactor = 0.05;  // environment, atmosphere

  vector<Mass> mass;
  vector<Spring> spring;

  void onCreate() override {
    mass.resize(3, Mass{});
    mass[0].x = 1;
    mass[0].mass = 0.11;

    mass[1].y = 1;
    mass[1].mass = 0.19;

    mass[2].x = 1;
    mass[2].y = 1;
    mass[2].mass = 0.27;

    spring.push_back({mass[0], mass[1], 1, 200});
    spring.push_back({mass[1], mass[2], 1, 300});
    spring.push_back({mass[2], mass[0], 1, 200});
  }

  void onAnimate(double dt) override {
    // caculate velocity change from forces
    for (Spring& s : spring) {
      Vec2f a2b = s.b - s.a;
      float forceMagnitude =  // Fs = -kx (Hooke's Law)
          (a2b.mag() - s.restLength) * s.stiffness;
      Vec2f unitVector = a2b / a2b.mag();  // now length 1 (unit) vector
      Vec2f force = unitVector * forceMagnitude;

      // equal and opposite forces
      s.a.velocity += force;
      s.b.velocity -= force;
    }

    // add drag
    for (Mass& m : mass) {
      m.velocity += -m.velocity * dragFactor;
    }

    // integrate velocity
    for (Mass& m : mass) {
      m += m.velocity * timeStep;
    }
  }

  void onDraw(Graphics& g) override {
    g.clear(0.25);
    g.camera(Viewpoint::IDENTITY);

    g.scale((float)height() / width(), 1, 1);  // correct aspect ratio

    g.scale(0.5);  // zoom out

    for (Mass& m : mass) {
      circle(g, m, m.mass);
    }
    for (Spring& s : spring) {
      line(g, s.a, s.b);
    }
  }

  void onKeyDown(const Keyboard& k) override {
    if (k.key() == ' ') {
      float angle = rnd::uniform(M_2PI);
      mass[0].velocity.x = 40 * sin(angle);
      mass[0].velocity.y = 40 * cos(angle);
    }
  }
};

int main() {
  MyApp app;
  app.initAudio();
  app.start();
}
