#version 400

uniform float time;   // time in seconds since the program started
uniform vec2 window;  // x means width, y means height, in pixels
uniform vec2 mouse;   // position of the mouse, in pixels
in vec2 pixel;        // position of this fragment on the screen
out vec4 color;       // (output) the color of this fragment

// TODO:
// - texture with audio spectrum
// - texture with last bit of audio waveform
// - texture with last graphics frame

void main() {
  float a = mouse.x / window.x;  // parameter on (0, 1)
  float b = mouse.y / window.y;  // parameter on (0, 1)
  float level = min(1.0, 20 * a / distance(mouse, pixel));

  vec4 fairy = vec4(1 - level, level, 0.5 + cos(time * 2) / 2, 1.0);
  vec4 oscillation = vec4(a, 1 / level, 0.5 + sin(time) / 2.0, 1.0);
  color = mix(fairy, oscillation, b);
}