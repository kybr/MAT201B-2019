#version 400

layout(lines) in;
layout(triangle_strip, max_vertices = 4) out;

uniform mat4 al_ProjectionMatrix;
uniform float strokeWeight;

void main() {
  mat4 m = al_ProjectionMatrix;  // rename to make lines shorter

  // al_ModelViewMatrix is already applied in the vertex shader
  vec4 a = gl_in[0].gl_Position;
  vec4 b = gl_in[1].gl_Position;

  // does vec3(0.0, 0.0, 1.0) point at the eye in the coordinate system?
  // we hope that this billboards; it seems to, but really?
  // XXX i think that this is broken; it's just not quite right
  vec4 d = vec4(normalize(cross(b.xyz - a.xyz, vec3(0.0, 0.0, 1.0))), 0.0) *
           strokeWeight;

  gl_Position = m * (a + d);
  EmitVertex();

  gl_Position = m * (a - d);
  EmitVertex();

  gl_Position = m * (b + d);
  EmitVertex();

  gl_Position = m * (b - d);
  EmitVertex();

  EndPrimitive();
}