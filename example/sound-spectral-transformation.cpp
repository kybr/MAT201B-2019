#include "al/core.hpp"
using namespace al;

#include "Gamma/DFT.h"  //STFT
#include "Gamma/SamplePlayer.h"
using namespace gam;

const int WINDOW_SIZE = 2048;
const int FFT_SIZE = 1 << 13;

STFT stft =
    STFT(WINDOW_SIZE, WINDOW_SIZE / 4, FFT_SIZE - WINDOW_SIZE, HANN, MAG_PHASE);

struct MyApp : App {
  SamplePlayer<float, gam::ipl::Linear, phsInc::Loop> samplePlayer;

  void onCreate() override {
    samplePlayer.load("../sound/8.wav");
    Sync::master().spu(audioIO().fps());
  }

  void onSound(AudioIOData& io) override {
    while (io()) {
      float mic = io.in(0) + io.in(1);
      // do something with the mic!

      float s = samplePlayer();
      if (stft(s)) {
        for (int i = 0; i < stft.numBins(); ++i) {
          stft.bin(i)[1] = 0;  // zero phase
        }
      }
      float f = stft();
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
