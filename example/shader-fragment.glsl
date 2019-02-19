#version 400
layout(location = 0) out vec4 fragmentColor;
uniform float time;
uniform vec2 window;
uniform vec2 mouse;
// XXX audio statistics
void main() {
  fragmentColor =
      vec4(mouse.x / window.x, mouse.y / window.y, 0.5 + sin(time) / 2.0, 1.0);
  //
}