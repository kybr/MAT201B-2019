#version 400

layout(location = 0) in vec3 vertexPosition;

uniform mat4 al_ModelViewMatrix;

void main() {
  //
  gl_Position = al_ModelViewMatrix * vec4(vertexPosition, 1.0);
}