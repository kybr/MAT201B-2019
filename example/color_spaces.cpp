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

    // you initialize...
    // position[1]
    // position[2]
    // position[3]
  }

  int target, last;  // use like position[target] or position[last]

  double timer = 0;
  void onAnimate(double dt) override {
    // dt is in seconds
    timer += dt;
    // timer is now the amount of time (in seconds) since the program started

    // http://paulbourke.net/miscellaneous/interpolation/

    // animate the positions of the mesh vertices
    // auto& vertexList = mesh.vertices();
    // for each vertex in the list above
    // interpolate (linear) between 'last' and 'target'
  }

  void onDraw(Graphics& g) override {
    g.clear(0.25);
    g.meshColor();  // alternative to g.color(1, 0, 0);
    g.draw(mesh);
  }

  void onKeyDown(const Keyboard& k) override {
    if (k.key() == '1') {
      // start process of animating to position[0]
    } else if (k.key() == '2') {
      // start process of animating to position[1]
    } else if (k.key() == '3') {
      // start process of animating to position[2]
    } else if (k.key() == '4') {
      // start process of animating to position[3]
    }
  }
};

int main() {
  MyApp app;
  app.start();
}
