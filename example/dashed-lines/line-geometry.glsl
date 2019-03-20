#version 330

layout(lines) in;
layout(triangle_strip, max_vertices = 4) out;

uniform mat4 al_ModelViewMatrix;
uniform mat4 al_ProjectionMatrix;
uniform vec3 al_EyePosition;
uniform float strokeWeight;

void main() {
  mat4 mv = al_ModelViewMatrix;
  mat4 p = al_ProjectionMatrix;
  vec3 e = al_EyePosition;

  vec4 a = gl_in[0].gl_Position;
  vec4 b = gl_in[1].gl_Position;

  vec4 d = vec4(normalize(cross(b.xyz - a.xyz, b.xyz - e)) * strokeWeight, 0.0);

  gl_Position = p * mv * (a + d);
  EmitVertex();

  gl_Position = p * mv * (a - d);
  EmitVertex();

  gl_Position = p * mv * (b + d);
  EmitVertex();

  gl_Position = p * mv * (b - d);
  EmitVertex();

  EndPrimitive();
}