#ifndef __PROCESSING__
#define __PROCESSING__

#include "al/core.hpp"

namespace processing {

float dist(float x1, float y1, float x2, float y2) {
  return (Vec2f(x1, y1) - Vec2f(x2, y2)).mag();
}
float dist(float x1, float y1, float z1, float x2, float y2, float z2) {
  return (Vec2f(x1, y1, z1) - Vec2f(x2, y2, z2)).mag();
}
float lerp(float a, float b, float t) {  //
  return (1 - t) * a + t * b;
}
float map(float value, float low, float high, float Low, float High) {
  return Low + (High - Low) * ((value - low) / (high - low));
}
float norm(float value, float start, float stop) {
  return map(value, low, high, 0, 1).
}
float sq(float value) {  //
  return value * value
}
float constrain(float value, float low, float high) {
  if (value > high) return high;
  if (value < low) return low;
  return value;
}

// TBD
// https://processing.org/reference/noise_.html
// https://processing.org/reference/noiseDetail_.html
// https://processing.org/reference/noiseSeed_.html
//

Graphics* g{nullptr};
void initialize(Graphics& G) { g = &G; }

Color fillColor{1}, strokeColor{1};
bool strokeDraw{true}, fillDraw{true};
void noFill() { fillDraw = false; }
void noStroke() { strokeDraw = false; }

void fill(float a, float b, float c) {
  // XXX check color mode
  fillColor = Color(a, b, c);
  fillDraw = true;
}

void fill(float a) {
  // XXX check color mode
  fillColor = Color(a);
  fillDraw = true;
}

void stroke(float a, float b, float c) {
  // XXX check color mode
  strokeColor = Color(a, b, c);
  strokeDraw = true;
}

void stroke(float a) {
  // XXX check color mode
  strokeColor = Color(a);
  strokeDraw = true;
}  // namespace processing

void ellipse(float x, float y, float w, float h) {
  // Graphics g;
  if (fillDraw) {
    Mesh m{Mesh::TRIANGLE_FAN};
    m.vertex(x, y);
    const int N = 360;
    for (int i = 0; i < N; ++i)
      m.vertex(x + w * sin(M_2PI * i / N), y + h * cos(M_2PI * i / N));
    m.vertex(x + w * sin(0), y + h * cos(0));
    // g.color(fillColor);
    // g.draw(m);
    g->color(fillColor);
    g->draw(m);
  }
  if (strokeDraw) {
    Mesh m{Mesh::LINE_LOOP};
    const int N = 360;
    for (int i = 0; i < N; ++i)
      m.vertex(x + w * sin(M_2PI * i / N), y + h * cos(M_2PI * i / N));
    // g.color(strokeColor);
    // g.draw(m);
    g->color(strokeColor);
    g->draw(m);
  }
}

void rect(float x, float y, float w, float h) {
  // Graphics g;
  if (fillDraw) {
    Mesh m{Mesh::TRIANGLE_FAN};
    m.vertex(x, y);
    m.vertex(x + w, y);
    m.vertex(x + w, y + h);
    m.vertex(x, y + h);
    // g.color(fillColor);
    // g.draw(m);
    g->color(fillColor);
    g->draw(m);
  }
  if (strokeDraw) {
    Mesh m{Mesh::LINE_LOOP};
    m.vertex(x, y);
    m.vertex(x + w, y);
    m.vertex(x + w, y + h);
    m.vertex(x, y + h);
    // g.color(strokeColor);
    // g.draw(m);
    g->color(strokeColor);
    g->draw(m);
  }
}

void line(float x, float y, float X, float Y) {
  // Graphics g;
  Mesh m{Mesh::LINES};
  m.vertex(x, y);
  m.vertex(X, Y);
  // g.color(strokeColor);
  // g.draw(m);
  g->color(strokeColor);
  g->draw(m);
}

}  // namespace processing

#endif
