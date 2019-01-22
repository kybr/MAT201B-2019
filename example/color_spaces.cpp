#include "al/core.hpp"
#include "al/util/al_Image.hpp"  // gets us Image
using namespace al;

struct MyApp : App {
  Texture texture;
  void onCreate() override {
    // load an image file
    Image image;
    const char* fileName = "../color_spaces.jpg";
    if (image.load(fileName)) {
      printf("Read image from %s\n", fileName);
    }
    image.sendToTexture(texture);
  }

  void onAnimate(double dt) override {
    // animate the positions of the mesh vertices
  }

  void onDraw(Graphics& g) override {
    g.clear(0.25);
    //
    // draw the pixel mesh

    g.translate(0, 0, -5);
    g.quad(texture, -1, -1, 2, 2);
  }

  void onKeyDown(const Keyboard& k) override {
    if (k.key() == '1') {
      printf("got a 1 key press\n");
    }
  }
};

int main() {
  MyApp app;
  app.start();
}
