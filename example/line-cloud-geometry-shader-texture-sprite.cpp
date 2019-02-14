#include "al/core.hpp"
using namespace al;

#include <vector>
using namespace std;

#define N (1000)
#define CLOUD_WIDTH (5.0)

const char* vertexPoint = R"(
#version 400

layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec4 vertexColor;
layout (location = 2) in vec2 vertexSize; // as a 2D texture cordinate, but we ignore the y

uniform mat4 al_ModelViewMatrix;
uniform mat4 al_ProjectionMatrix;

out Vertex {
  vec4 color;
  float size;
} vertex;

void main() {
  gl_Position = al_ModelViewMatrix * vec4(vertexPosition, 1.0);
  vertex.color = vertexColor;
  vertex.size = vertexSize.x;
}
)";

const char* fragmentPoint = R"(
#version 400

in Fragment {
  vec4 color;
  vec2 textureCoordinate;
} fragment;

uniform sampler2D alphaTexture;

layout (location = 0) out vec4 fragmentColor;

void main() {
  // use the first 3 components of the color (xyz is rgb), but take the alpha value from the texture
  //
  fragmentColor = vec4(fragment.color.xyz, texture(alphaTexture, fragment.textureCoordinate));
}
)";

const char* geometryPoint = R"(
#version 400

// take in a point and output a triangle strip with 4 vertices (aka a "quad")
//
layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

uniform mat4 al_ProjectionMatrix;

in Vertex {
  vec4 color;
  float size;
} vertex[];

out Fragment {
  vec4 color;
  vec2 textureCoordinate;
} fragment;

void main() {
  mat4 m = al_ProjectionMatrix; // rename to make lines shorter
  vec4 v = gl_in[0].gl_Position; // al_ModelViewMatrix * gl_Position

  float r = 0.15;
  r *= vertex[0].size;

  gl_Position = m * (v + vec4(-r, -r, 0.0, 0.0));
  fragment.textureCoordinate = vec2(0.0, 0.0);
  fragment.color = vertex[0].color;
  EmitVertex();

  gl_Position = m * (v + vec4(r, -r, 0.0, 0.0));
  fragment.textureCoordinate = vec2(1.0, 0.0);
  fragment.color = vertex[0].color;
  EmitVertex();

  gl_Position = m * (v + vec4(-r, r, 0.0, 0.0));
  fragment.textureCoordinate = vec2(0.0, 1.0);
  fragment.color = vertex[0].color;
  EmitVertex();

  gl_Position = m * (v + vec4(r, r, 0.0, 0.0));
  fragment.textureCoordinate = vec2(1.0, 1.0);
  fragment.color = vertex[0].color;
  EmitVertex();

  EndPrimitive();
}
)";

const char* vertexLine = R"(
#version 400

layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec4 vertexColor;
layout (location = 2) in vec2 vertexSize; // as a 2D texture cordinate, but we ignore the y

out Vertex {
  vec4 color;
  float size;
} vertex;

uniform mat4 al_ModelViewMatrix;
uniform mat4 al_ProjectionMatrix;

void main() {
  gl_Position = al_ModelViewMatrix * vec4(vertexPosition, 1.0);
  vertex.color = vertexColor;
  vertex.size = vertexSize.x;
}
)";

const char* fragmentLine = R"(
#version 400

in Fragment {
  vec4 color;
  float textureCoordinate;
} fragment;

uniform sampler1D alphaTexture;

layout (location = 0) out vec4 fragmentColor;

void main() {
  fragmentColor = vec4(fragment.color.xyz, texture(alphaTexture, fragment.textureCoordinate));
}
)";

const char* geometryLine = R"(
#version 400

layout (lines) in;
layout (triangle_strip, max_vertices = 4) out;

uniform mat4 al_ProjectionMatrix;

in Vertex {
  vec4 color;
  float size;
} vertex[];

out Fragment {
  vec4 color;
  float textureCoordinate;
} fragment;

void main() {
  mat4 m = al_ProjectionMatrix; // rename to make lines shorter
  vec4 a = gl_in[0].gl_Position;
  vec4 b = gl_in[1].gl_Position;

  const float r = 0.03;

  // does vec3(0.0, 0.0, 1.0) point at the eye in the coordinate system?
  // we hope that this billboards; it seems to, but really?
  // XXX i think that this is broken; it's just not quite right
  vec4 d = vec4(normalize(cross(b.xyz - a.xyz, vec3(0.0, 0.0, 1.0))), 0.0) * r;

  gl_Position = m * (a + d * vertex[0].size);
  fragment.color = vertex[0].color;
  fragment.textureCoordinate = 0.0;
  EmitVertex();

  gl_Position = m * (a - d * vertex[0].size);
  fragment.color = vertex[0].color;
  fragment.textureCoordinate = 1.0;
  EmitVertex();

  gl_Position = m * (b + d * vertex[1].size);
  fragment.color = vertex[1].color;
  fragment.textureCoordinate = 0.0;
  EmitVertex();

  gl_Position = m * (b - d * vertex[1].size);
  fragment.color = vertex[1].color;
  fragment.textureCoordinate = 1.0;
  EmitVertex();

  EndPrimitive();
}
)";

struct AlloApp : App {
  ShaderProgram pointShader;
  ShaderProgram lineShader;
  Texture pointTexture;
  Texture lineTexture;
  Mesh mesh;

  void onCreate() override {
    // use a texture to control the alpha channel of each particle
    //
    pointTexture.create2D(256, 256, Texture::R8, Texture::RED, Texture::SHORT);
    int Nx = pointTexture.width();
    int Ny = pointTexture.height();
    std::vector<short> alpha;
    alpha.resize(Nx * Ny);
    for (int j = 0; j < Ny; ++j) {
      float y = float(j) / (Ny - 1) * 2 - 1;
      for (int i = 0; i < Nx; ++i) {
        float x = float(i) / (Nx - 1) * 2 - 1;
        float m = exp(-13 * (x * x + y * y));
        m *= pow(2, 15) - 1;  // scale by the largest positive short int
        alpha[j * Nx + i] = m;
      }
    }
    pointTexture.submit(&alpha[0]);

    lineTexture.create1D(256, Texture::R8, Texture::RED, Texture::SHORT);
    std::vector<short> beta;
    beta.resize(lineTexture.width());
    for (int i = 0; i < beta.size(); ++i) {
      beta[i] = alpha[128 * beta.size() + i];
    }
    lineTexture.submit(&beta[0]);

    // compile and link the shaders
    //
    pointShader.compile(vertexPoint, fragmentPoint, geometryPoint);
    lineShader.compile(vertexLine, fragmentLine, geometryLine);

    // create a mesh of points scattered randomly with random colors
    //
    mesh.primitive(Mesh::LINES);
    for (int i = 0; i < N; i++) {
      mesh.vertex(Vec3f(rnd::uniformS(), rnd::uniformS(), rnd::uniformS()) *
                  CLOUD_WIDTH);
      mesh.color(HSV(rnd::uniform(), 1.0, 1.0));
      mesh.texCoord(rnd::uniform(0.5, 0.05), 0.0);
    }

    // this means something different than re-positioning. it changes the
    // position of the camera with respect to the nav position, making a sort of
    // "third person" camera
    // nav().pullBack(9);
  }

  void onAnimate(double dt) override {}

  void onDraw(Graphics& g) override {
    g.clear(0.23);

    // still TBD, OIT (Order Independent Tranparency)
    //
    g.depthTesting(false);
    g.blending(true);
    g.blendModeTrans();

    pointTexture.bind();
    g.shader(pointShader);
    mesh.primitive(Mesh::POINTS);
    g.draw(mesh);
    pointTexture.unbind();

    lineTexture.bind();
    g.shader(lineShader);
    mesh.primitive(Mesh::LINES);
    g.draw(mesh);
    lineTexture.unbind();
  }
};

int main() { AlloApp().start(); }