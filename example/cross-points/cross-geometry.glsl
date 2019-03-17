#version 400
//
layout(points) in;
layout(triangle_strip, max_vertices = 4) out;

uniform mat4 al_ProjectionMatrix;

uniform vec2 shape;

void main() {
  mat4 m = al_ProjectionMatrix;
  // al_ModelViewMatrix * gl_Position
  vec4 v = gl_in[0].gl_Position;

  gl_Position = m * (v + vec4(-shape.x, -shape.y, 0.0, 0.0));
  EmitVertex();

  gl_Position = m * (v + vec4(shape.x, -shape.y, 0.0, 0.0));
  EmitVertex();

  gl_Position = m * (v + vec4(-shape.x, shape.y, 0.0, 0.0));
  EmitVertex();

  gl_Position = m * (v + vec4(shape.x, shape.y, 0.0, 0.0));
  EmitVertex();
  EndPrimitive();
}