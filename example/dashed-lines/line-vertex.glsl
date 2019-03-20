#version 330
// #version 400

layout(location = 0) in vec3 vertexPosition;

uniform mat4 al_ModelViewMatrix;
uniform mat4 al_ProjectionMatrix;

void main() {
  //
  gl_Position = al_ModelViewMatrix * vec4(vertexPosition, 1.0);
}