const char* vertexCode = R"(
#version 400

layout (location = 0) in vec3 vertexPosition;

uniform mat4 al_ModelViewMatrix;
uniform mat4 al_ProjectionMatrix;

out vec2 pixel;

void main() {
  gl_Position = al_ProjectionMatrix * al_ModelViewMatrix * vec4(vertexPosition, 1.0);
  pixel = vertexPosition.xy;
}
)";