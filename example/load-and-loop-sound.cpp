#include "al/core.hpp"
using namespace al;

#include "Gamma/SamplePlayer.h"
using namespace gam;

struct MyApp : App {
  SamplePlayer<float, gam::ipl::Linear, phsInc::Loop> samplePlayer;

  void onCreate() override {
    samplePlayer.load("../6.wav");
    samplePlayer.loop();
    Sync::master().spu(audioIO().fps());
  }

  void onSound(AudioIOData& io) override {
    while (io()) {
      float f = samplePlayer();
      io.out(0) = f;
      io.out(1) = f;
    }
  }
};

int main() {
  MyApp app;
  app.initAudio();
  app.start();
}
