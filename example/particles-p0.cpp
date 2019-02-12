#include "al/core.hpp"
using namespace al;

#include <vector>
using namespace std;

#define N (1000)  // number of particles
#define CLOUD_WIDTH (5.0)

const char* vertex = R"(
#version 400

layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec4 vertexColor;

uniform mat4 al_ModelViewMatrix;
uniform mat4 al_ProjectionMatrix;

out Vertex {
  vec4 color;
} vertex;

void main() {
  gl_Position = al_ModelViewMatrix * vec4(vertexPosition, 1.0);
  vertex.color = vertexColor;
}
)";

const char* fragment = R"(
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

const char* geometry = R"(
#version 400

// take in a point and output a triangle strip with 4 vertices (aka a "quad")
//
layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

uniform mat4 al_ProjectionMatrix;

// this uniform is *not* passed in automatically by AlloLib; do it manually
//
uniform float halfSize;

in Vertex {
  vec4 color;
} vertex[];

out Fragment {
  vec4 color;
  vec2 textureCoordinate;
} fragment;

void main() {
  mat4 m = al_ProjectionMatrix; // rename to make lines shorter
  vec4 v = gl_in[0].gl_Position; // al_ModelViewMatrix * gl_Position

  gl_Position = m * (v + vec4(-halfSize, -halfSize, 0.0, 0.0));
  fragment.textureCoordinate = vec2(0.0, 0.0);
  fragment.color = vertex[0].color;
  EmitVertex();

  gl_Position = m * (v + vec4(halfSize, -halfSize, 0.0, 0.0));
  fragment.textureCoordinate = vec2(1.0, 0.0);
  fragment.color = vertex[0].color;
  EmitVertex();

  gl_Position = m * (v + vec4(-halfSize, halfSize, 0.0, 0.0));
  fragment.textureCoordinate = vec2(0.0, 1.0);
  fragment.color = vertex[0].color;
  EmitVertex();

  gl_Position = m * (v + vec4(halfSize, halfSize, 0.0, 0.0));
  fragment.textureCoordinate = vec2(1.0, 1.0);
  fragment.color = vertex[0].color;
  EmitVertex();

  EndPrimitive();
}
)";

struct AlloApp : App {
  ShaderProgram shader;
  Texture texture;

  // simulation parameters
  double timeStep = 0.001;
  double dragFactor = 0.05;

  Mesh pointMesh;          // holds positions
  vector<float> mass;      // holds masses
  vector<Vec3f> velocity;  // holds velocities

  void onCreate() override {
    // use a texture to control the alpha channel of each particle
    //
    texture.create2D(256, 256, Texture::R8, Texture::RED, Texture::SHORT);
    int Nx = texture.width();
    int Ny = texture.height();
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
    texture.submit(&alpha[0]);

    // compile and link the three shaders
    //
    shader.compile(vertex, fragment, geometry);

    // create a mesh of points scattered randomly with random colors
    //
    pointMesh.primitive(Mesh::POINTS);
    for (int i = 0; i < N; i++) {
      pointMesh.vertex(
          Vec3f(rnd::uniformS(), rnd::uniformS(), rnd::uniformS()) *
          CLOUD_WIDTH);
      pointMesh.color(HSV(rnd::uniform(), 1.0, 1.0));
    }

    // put your setup code here
    //
    // you need to initialize velocities
  }

  void onAnimate(double dt) override {
    // put your simulation code here
    //

    vector<Vec3f>& vertex(pointMesh.vertices());  // make an alias

    // add a random vector to each mass
    for (int i = 0; i < vertex.size(); ++i) {
      vertex[i] +=
          Vec3f(rnd::uniformS(1.0f), rnd::uniformS(1.0f), rnd::uniformS(1.0f)) *
          0.01;
    }

    // for each pair (i,j)...
    for (int i = 0; i < vertex.size(); ++i) {
      for (int j = 1 + i; j < vertex.size(); ++j) {
        Vec3f& a(vertex[i]);  // alias
        Vec3f& b(vertex[j]);  // alias

        // mass of i is mass[i]
        // mass of j is mass[j]
        // velocity of a is velocity[i]
        // velocity of b is velocity[j]

        // Fij =    G * Mi * Mj
        //       ---------------- * Uij
        //        distance(ij)^2
        // where Uij is the unit vector from i to j
        //
      }
    }

    // F = ma
    // 1. calculate gravitational forces
    // 2. accumulate accellerations into velocities
    // 3. add drag forces to velocities
    // 4. accumulate velocity into position
  }

  void onDraw(Graphics& g) override {
    // you don't have to change anything in here
    //
    g.clear(0.23);

    g.depthTesting(false);
    g.blending(true);
    g.blendModeTrans();

    texture.bind();
    g.shader(shader);
    g.shader().uniform("halfSize", 0.15);
    g.draw(pointMesh);
    texture.unbind();
  }
};

int main() { AlloApp().start(); }