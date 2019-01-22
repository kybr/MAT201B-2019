#include "al/core.hpp"
using namespace al;

struct MyApp : App {
  // onCreate is called before anything else and is only called one time
  void onCreate() override {
    // put things here that you can to setup

    // initialize things here
  }

  // onAnimate is called once per frame, right before onDraw
  // at about 60 Hz
  double timer = 0;
  void onAnimate(double dt) override {
    timer += dt;
    if (timer > 3) {
      timer -= 3;
      shouldFlash = true;
      shouldClick = true;
    }

    // change the "virtual world" here, once per frame

    // don't try to draw things here
  }

  // onDraw may be called many times per frame
  // probably at 60 Hz or close to that
  // for instance, per-eye in stereo 3D graphics
  // it is called after onAnimate
  void onDraw(Graphics& g) override {
    g.clear(0.25);  // set the background color to grey

    g.clear(mouseX / width(), 0, mouseY / height());

    if (shouldFlash) {
      shouldFlash = false;
      g.clear(1);
    }

    // only draw things here

    // don't try to change the "virtual world"
  }

  // onSound is called over and over at ~80-500 Hz
  double phase = 0;
  void onSound(AudioIOData& io) override {
    while (io()) {
      phase += 0.003;
      if (phase > 1) phase -= 2;
      float s = phase;
      if (shouldClick) {
        shouldClick = false;
        s = 1;
      }
      io.out(0) = s;
      io.out(1) = s;
    }
  }

  bool shouldClick = false;
  bool shouldFlash = false;
  void onKeyDown(const Keyboard& k) override {
    if (k.key() == ' ') {
      shouldClick = true;
      shouldFlash = true;
    }
  }

  float mouseX, mouseY;
  void onMouseMove(Mouse const& m) override {
    mouseX = m.x();
    mouseY = m.y();
  }
};

int main() {
  MyApp app;
  app.initAudio();
  app.start();  // starts a loop that calls onAnimate, onDraw, onSound, etc.
                // after first calling onCreate
}
