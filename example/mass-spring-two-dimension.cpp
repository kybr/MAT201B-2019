#include "al/core.hpp"
using namespace al;

#include <vector>
using namespace std;

// make this 2d
// make multiple masses and springs

// 3 masses, 3 springs, in a triangle

void ellipse(Graphics& g, float x, float y, float w, float h) {
  Mesh m{Mesh::TRIANGLE_FAN};
  m.vertex(x, y);
  for (int i = 0; i < 101; ++i)
    m.vertex(x + w * sin(M_2PI * i / 100), y + h * cos(M_2PI * i / 100));
  g.color(1);
  g.draw(m);
}

void line(Graphics& g, float x0, float y0, float x1, float y1) {
  Mesh m{Mesh::LINES};
  m.vertex(x0, y0);
  m.vertex(x1, y1);
  g.color(1);
  g.draw(m);
}

struct Mass {
  float mass;
  Vec2f position, velocity;
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
    mass.push_back({0.11, {0, 0}, {0, 0}});
    mass.push_back({0.19, {1, 0}, {0, 0}});
    mass.push_back({0.27, {0, 1}, {0, 0}});
    spring.push_back({mass[0], mass[1], 1, 200});
    spring.push_back({mass[1], mass[2], 1, 300});
    spring.push_back({mass[2], mass[0], 1, 200});
  }

  void onAnimate(double dt) override {
    // caculate velocity change from forces
    for (Spring& s : spring) {
      Vec2f a2b = s.b.position - s.a.position;
      float forceMagnitude =  // Fs = -kx (Hooke's Law)
          (a2b.mag() - s.restLength) * s.stiffness;
      Vec2f unitVector = a2b / a2b.mag();  // now length 1 (unit) vector
      Vec2f force = unitVector * forceMagnitude;
      s.a.velocity += force;
      s.b.velocity -= force;
    }

    // drag
    for (Mass& m : mass) {
      m.velocity += -m.velocity * dragFactor;
    }

    // integrate velocity

    for (Mass& m : mass) {
      m.position += m.velocity * timeStep;
    }

    // mass[0].position.print();
    // cout << endl;
  }

  void onDraw(Graphics& g) override {
    g.clear(0.25);
    g.camera(Viewpoint::IDENTITY);

    g.scale((float)height() / width(), 1, 1);  // correct aspect ratio

    g.scale(0.5);  // zoom out

    for (Mass& m : mass) {
      ellipse(g, m.position.x, m.position.y, m.mass, m.mass);
    }
    // for (Type name : container) { /* body */ }
    // for (Type& name : container) { /* body */ }
    // for (auto& name : container) { /* body */ }
    // for (auto& name : vector<??>) { /* body */ }
    for (Spring& s : spring) {
      line(g, s.a.position.x, s.a.position.y, s.b.position.x, s.b.position.y);
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
