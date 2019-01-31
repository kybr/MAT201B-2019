#include "al/core.hpp"
#include "al/util/al_Image.hpp"
using namespace al;

#include <cassert>
#include <cstdint>
#include <iostream>
#include <vector>
using namespace std;

struct MyApp : App {
  Mesh mesh{Mesh::POINTS};
  vector<Vec3f> position[4];

  void onCreate() override {
    Image image;
    const char* fileName = "../color_spaces.jpg";
    if (!image.load(fileName)) {
      printf("Failed to read image from %s! Quitting.\n", fileName);
      exit(-1);
    }

    Image::RGBAPix<uint8_t> pixel;
    for (size_t row = 0; row < image.height(); ++row) {
      for (size_t column = 0; column < image.width(); ++column) {
        // image.array().read(&pixel, column, row);
        // image.array().read(&pixel.r, column, row);
        image.read(pixel, column, row);
        mesh.vertex((float)column / image.width(), (float)row / image.width());
        mesh.color(pixel.r / 256.0, pixel.g / 256.0, pixel.b / 256.0);
      }
    }

    // original (image) positions
    //
    for (auto& v : mesh.vertices()) position[0].push_back(Vec3f(v.x, v.y, 0));

    // RGB as XYZ
    //
    for (auto& c : mesh.colors()) position[1].push_back(Vec3f(c.r, c.g, c.b));

    // HSV cylinder
    //
    for (HSV c : mesh.colors())
      position[2].push_back(
          Vec3f(c.s * sin(c.h * M_2PI), c.s * cos(c.h * M_2PI), c.v));

    // random positions
    //
    for (int i = 0; i < position[0].size(); ++i)
      position[3].push_back(
          Vec3f(rnd::uniform(1.0), rnd::uniform(1.0), rnd::uniform(1.0)));
  }

  float t = 3;
  void onAnimate(double dt) override {
    t += dt;
    if (t < 1) {
      auto& m = mesh.vertices();
      for (int i = 0; i < m.size(); ++i)
        m[i].set(position[target_][i] * (1 - t) + position[target][i] * t);
    } else if (t > 2) {
      // do nothing
    } else {
      auto m = mesh.vertices();
      for (int i = 0; i < m.size(); ++i) m[i] = position[target][i];
      t = 3;
    }
  }

  int target = 0, target_ = 0;

  void onKeyDown(const Keyboard& k) override {
    if (k.key() >= '1' && k.key() <= '4') {
      target_ = target;
      target = k.key() - '1';
      t = 0;
    }
  }

  void onDraw(Graphics& g) override {
    g.clear(0.2);
    g.meshColor();
    g.draw(mesh);
  }
};

int main() {
  MyApp app;
  app.start();
}
