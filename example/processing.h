#ifndef __PROCESSING__
#define __PROCESSING__

#include "al/core.hpp"

namespace processing {

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
