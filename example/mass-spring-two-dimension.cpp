#include "al/core.hpp"
using namespace al;

#include <vector>
using namespace std;

// draw a circle, given a 2D point and a radius
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

// Earlier, I defined Mass like this:
//
// struct Mass {
//   Vec2f position;
//   Vec2f velocity;
//   float mass;
// };
//
// Mass m;
// m.position.x = 3.9;
//
// I changed the definition of Mass to "inherit" from Vec2f so that we can treat
// it as its own position. Below, we say that Mass *is* a Vec2f which represents
// its position. As well, it has a Vec2f for velocity.
//
struct Mass : Vec2f {
  Vec2f velocity;
  float mass;
};
//
// Mass m;
// m.x = 3.9;

struct Spring {
  Mass& a;  // a reference to a Mass
  Mass& b;
  float restLength;
  float stiffness;
};

struct MyApp : App {
  // simulation parameters
  double timeStep = 0.001;
  double dragFactor = 0.05;

  vector<Mass> mass;
  vector<Spring> spring;

  Mass mouse;

  void onCreate() override {
    mouse.set(0, 0);
    mouse.mass = 1;
    mouse.velocity.set(0, 0);

    mass.resize(4, Mass{});
    // mass[0].set(0, 0); // XXX bad; don't put masses on top of eachother
    mass[0].set(-0.5, 0);
    mass[0].mass = 0.11;
    mass[1].set(1, 0);
    mass[1].mass = 0.19;
    mass[2].set(1, 1);
    mass[2].mass = 0.27;
    mass[3].set(0, 1.1);
    mass[3].mass = 0.17;

    spring.push_back({mouse, mass[0], 0.1, 150});
    spring.push_back({mass[0], mass[1], 1, 200});
    spring.push_back({mass[1], mass[2], 1, 300});
    spring.push_back({mass[2], mass[0], 1, 200});
    spring.push_back({mass[2], mass[3], 1, 200});
  }

  void onAnimate(double dt) override {
    // For each Spring...
    for (Spring& s : spring) {
      // Make a vector that points from a to b.
      Vec2f a2b = s.b - s.a;
      // Vec2f a2b = s.b.position - s.a.position;

      // Use Hooke's Law (Fs = -kx) to calculate the amount of force this
      // Spring will exert on each Mass. Know that .mag() computes the length (a
      // scalar) of a vector.
      float forceMagnitude = (a2b.mag() - s.restLength) * s.stiffness;

      // create a "unit vector" (a vector with length 1.0) that points in the
      // direction of the Spring.

      Vec2f unitVector = a2b / a2b.mag();  // is mag() is 0, we get NaNs

      Vec2f force = unitVector * forceMagnitude;

      // this is an alternative to the method above; normalize prevents NaNs
      // a2b.normalize();
      // Vec2f force = a2b * forceMagnitude;

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

    // Establish a coordinate system where the window goes from (-1, -1) on the
    // bottom left corner and (1, 1) on the top right corner.
    g.camera(Viewpoint::IDENTITY);

    // scale the x dimension to correct the aspect ratio
    g.scale((float)height() / width(), 1, 1);

    // scale *all* dimensions; this will "zoom out".
    g.scale(0.5);

    for (Mass& m : mass) {
      circle(g, m, m.mass);
    }
    for (Spring& s : spring) {
      line(g, s.a, s.b);
    }
  }

  void onKeyDown(const Keyboard& k) override {
    // Kick Mass 0 in a random direction when the space bar is pressed
    if (k.key() == ' ') {
      float angle = rnd::uniform(M_2PI);
      mass[0].velocity.x = 40 * sin(angle);
      mass[0].velocity.y = 40 * cos(angle);
    }
  }

  Vec2f transform(const Vec2f& v) {
    // assume: v is in pixel space
    // return: custom space

    Vec2f w;
    w.x = v.x;
    w.x /= width();  // 0,1
    w.x *= 2;        // 0,2
    w.x -= 1;        // -1,1
    w.x *= (float)width() / height();

    w.y = height() - v.y;  // pixels (flip y)
    w.y /= height();       // 0,1
    w.y *= 2;              // 0,2
    w.y -= 1;              // -1,1

    w *= 2;

    return w;
  }

  void onMouseDrag(const Mouse& m) override {
    // transform the mouse coordinates into our custom coordinate system
    mouse.set(transform(Vec2f(m.x(), m.y())));
  }

  void onMouseDown(const Mouse& m) override {
    for (Mass& M : mass) {
      Vec2f t = transform(Vec2f(m.x(), m.y()));
      if ((M - t).mag() < M.mass) {
        // its a hit!
        cout << "its a hit" << endl;
        // connect a spring between this mass and the mouse mass
      }
    }
  }
};

int main() {
  MyApp app;
  app.initAudio();
  app.start();
}