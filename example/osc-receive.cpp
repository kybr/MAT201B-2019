#include "al/core.hpp"
using namespace al;

struct MyApp : App {
  int proximity;

  void onMessage(osc::Message& m) override {
    if (m.addressPattern() == "/proximity")  //
      m >> proximity;
  }

  void onDraw(Graphics& g) override {
    g.clear(proximity / 255.0);
    //
  }
};

int main() {
  MyApp app;
  app.initAudio();
  app.start();
}
