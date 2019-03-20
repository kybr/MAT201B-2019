#version 330

layout(lines) in;
layout(triangle_strip, max_vertices = 4) out;

uniform mat4 al_ModelViewMatrix;
uniform mat4 al_ProjectionMatrix;
uniform vec3 al_EyePosition;
uniform float strokeWeight;

out struct Vertex {
  float value;
  float away;
} vertex;

void main() {
  mat4 p = al_ProjectionMatrix;  // rename to make lines shorter
  mat4 mv = al_ModelViewMatrix;  // rename to make lines shorter
  vec3 e = al_EyePosition;       // rename to make lines shorter

  vec4 a = gl_in[0].gl_Position;
  vec4 b = gl_in[1].gl_Position;

  vec4 d = vec4(normalize(cross(b.xyz - a.xyz, b.xyz - e)) * strokeWeight, 0.0);

  gl_Position = p * mv * (a + d);
  vertex.value = -1;
  vertex.away = length(a.xyz - e);
  EmitVertex();

  gl_Position = p * mv * (a - d);
  vertex.value = 1;
  vertex.away = length(a.xyz - e);
  EmitVertex();

  gl_Position = p * mv * (b + d);
  vertex.value = -1;
  vertex.away = length(b.xyz - e);
  EmitVertex();

  gl_Position = p * mv * (b - d);
  vertex.value = 1;
  vertex.away = length(b.xyz - e);
  EmitVertex();

  EndPrimitive();
}