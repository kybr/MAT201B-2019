#include "al/core.hpp"
#include "al/util/al_Image.hpp"  // gets us Image
using namespace al;
using namespace std;

struct MyApp : App {
  Mesh mesh{Mesh::POINTS};
  vector<Vec3f> position[4];  // an array of 4 vectors of Vec3f
  // position[0] is the original "image"-coordinates
  // position[1] is the RGB
  // position[2] is the HSV cylinder
  // position[3] is your choice

  void onCreate() override {
    Image image;
    const char* fileName = "../color_spaces.jpg";
    if (!image.load(fileName)) {
      exit(1);
    }

    nav().pullBack(7);

    Image::RGBAPix<uint8_t> pixel;
    for (int row = 0; row < image.height(); row++) {
      for (int column = 0; column < image.width(); column++) {
        image.read(pixel, column, row);  // read pixel data
        float x = (float)column / image.width() - 0.5;
        float y = (float)row / image.width() - 0.5;
        mesh.vertex(x, y, 0);
        position[0].push_back(Vec3f(x, y, 0));
        mesh.color(pixel.r / 256.0, pixel.g / 256.0, pixel.b / 256.0);
      }
    }

    for (const Color& c : mesh.colors())
      position[1].push_back(Vec3f(c.r, c.g, c.b) - Vec3f(0.5, 0.5, 0.5));
    // position[1].push_back(Vec3f(c.r - 0.5, c.g - 0.5, c.b - 0.5));

    const auto& c = mesh.colors();
    for (int i = 0; i < c.size(); ++i) {
      HSV color(c[i]);  // "convert" to HSV from RGB
      Vec3f v;
      // convert from polar to cartesian
      v.x = color.s * sin(M_2PI * color.h);
      v.y = color.s * cos(M_2PI * color.h);
      v.z = color.v;
      position[2].push_back(v);
    }
    for (int i = 0; i < c.size(); ++i)
      position[3].push_back(
          Vec3f(rnd::uniformS(), rnd::uniformS(), rnd::uniformS()));
  }

  int target = 0;
  int previousTarget =
      0;  // use like position[target] or position[previousTarget]

  // previousTarget was named last

  double t = 0;
  void onAnimate(double dt) override {
    t += dt;
    if (t > 0 && t < 1) {
      auto& m = mesh.vertices();
      for (int i = 0; i < m.size(); ++i)
        m[i] = position[previousTarget][i] * (1 - t) + position[target][i] * t;
    }
  }

  void onDraw(Graphics& g) override {
    g.clear(0.25);
    g.meshColor();  // alternative to g.color(1, 0, 0);
    g.draw(mesh);
  }

  void onKeyDown(const Keyboard& k) override {
    if (k.key() == '1') {
      // start process of animating to position[0]
      t = 0;
      previousTarget = target;
      target = 0;
    } else if (k.key() == '2') {
      // start process of animating to position[1]
      t = 0;
      previousTarget = target;
      target = 1;
    } else if (k.key() == '3') {
      // start process of animating to position[2]
      t = 0;
      previousTarget = target;
      target = 2;
    } else if (k.key() == '4') {
      // start process of animating to position[3]
      t = 0;
      previousTarget = target;
      target = 3;
    }
  }
};

int main() {
  MyApp app;
  app.start();
}
