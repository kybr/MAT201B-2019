#version 400

in Fragment {
  vec4 color;
  float textureCoordinate;
}
fragment;

uniform sampler1D alphaTexture;

layout(location = 0) out vec4 fragmentColor;

void main() {
  // fragmentColor = vec4(1.0, 1.0, 1.0, 1.0);
  // fragmentColor = vec4(1.0, 1.0, 1.0, texture(alphaTexture,
  // fragment.textureCoordinate));
  fragmentColor = vec4(fragment.color.xyz,
                       texture(alphaTexture, fragment.textureCoordinate));
}