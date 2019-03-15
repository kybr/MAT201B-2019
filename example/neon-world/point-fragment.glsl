#version 400

in Fragment {
  vec4 color;
  vec2 textureCoordinate;
}
fragment;

uniform sampler2D alphaTexture;

layout(location = 0) out vec4 fragmentColor;

void main() {
  // use the first 3 components of the color (xyz is rgb), but take the alpha
  // value from the texture
  //
  // fragmentColor = vec4(fragment.color.xyz, 1.0);
  fragmentColor = vec4(fragment.color.xyz,
                       texture(alphaTexture, fragment.textureCoordinate));
}