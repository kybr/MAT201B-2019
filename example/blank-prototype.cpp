#include "al/core.hpp"
using namespace al;

struct MyApp : App {
  void onCreate() override {
    //
  }

  void onAnimate(double dt) override {
    //
  }

  void onDraw(Graphics& g) override {
    g.clear(0.25);
    //
  }

  void onKeyDown(const Keyboard& k) override {
    //
  }
};

int main() {
  MyApp app;
  app.start();
}
