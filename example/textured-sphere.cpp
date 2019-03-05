#include "al/core.hpp"
// TODO: figure out how to handle include dirs for modules
#include "module/img/loadImage.hpp"

using namespace al;
using namespace std;

struct MyApp : App {
  Texture t;
  Mesh m;

  void onCreate() {
    auto imageData = imgModule::loadImage("../image/eye.jpg");
    if (imageData.data.size() == 0) {
      cout << "failed to load image" << endl;
    }
    t.create2D(imageData.width, imageData.height);
    t.submit(imageData.data.data(), GL_RGBA, GL_UNSIGNED_BYTE);

    addSphereWithTexcoords(m);
    m.generateNormals();
  }

  void onDraw(Graphics& g) {
    g.clear(0.2);
    g.depthTesting(true);
    t.bind();
    g.texture();
    g.draw(m);
  }
};

int main() {
  MyApp app;
  app.start();
}
