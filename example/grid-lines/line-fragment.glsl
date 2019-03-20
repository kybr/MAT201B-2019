#version 330

layout(location = 0) out vec4 fragmentColor;

in struct Vertex {
  float value;
  float away;
} vertex;

void main() {
  //
  fragmentColor = vec4(1.0, 1.0, 1.0,
                       (1 - vertex.value * vertex.value) *
                           clamp(10.0 / (vertex.away), 0.0, 1.0));
}