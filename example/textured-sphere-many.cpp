#include "al/core.hpp"
// TODO: figure out how to handle include dirs for modules
#include "module/img/loadImage.hpp"

using namespace al;
using namespace std;

Vec3f r(float m = 1) {
  return Vec3f(rnd::uniformS(), rnd::uniformS(), rnd::uniformS()) * m;
}

struct MyApp : App {
  Texture t;
  Mesh m;
  vector<Vec3f> eye;

  void onCreate() {
    auto imageData = imgModule::loadImage("../image/eye.jpg");
    if (imageData.data.size() == 0) {
      cout << "failed to load image" << endl;
    }
    t.create2D(imageData.width, imageData.height);
    t.submit(imageData.data.data(), GL_RGBA, GL_UNSIGNED_BYTE);

    addSphereWithTexcoords(m);
    m.generateNormals();

    for (int i = 0; i < 10; i++) {
      eye.push_back(r(5));
    }

    nav().pos(0, 0, 10);
  }

  void onDraw(Graphics& g) {
    g.clear(0.2);
    g.depthTesting(true);
    t.bind();
    g.texture();
    for (auto& p : eye) {
      g.pushMatrix();
      g.translate(p);
      g.draw(m);
      g.popMatrix();
    }
  }
};

int main() {
  MyApp app;
  app.start();
}
