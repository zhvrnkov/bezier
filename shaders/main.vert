#version 430 core

struct BezierNode {
  vec2 a;
  vec2 b;
  vec2 p1;
  vec2 p2;
  vec3 color;
  float lineWidth;
};

layout (location = 0) in vec2 aPos;

uniform int elementsPerInstance;
uniform BezierNode nodes[200];
uniform vec3 colors[3];

out vec3 VertexColor;

void main() {
  BezierNode node = nodes[gl_InstanceID];

  vec2 bFromA = node.b - node.a;
  vec2 instanceStep = bFromA / float(1);
  vec2 triangleBase = node.a;// + (float(gl_VertexID / 3) * instanceStep);
  float length = float(gl_VertexID % 2) - 0.5;
  // if (gl_VertexID % 2 == 1) {
  //   length = -length;
  // }
  vec2 tangent = normalize(vec2(-bFromA.y, bFromA.x));
  gl_Position = vec4(triangleBase + (tangent * length) + instanceStep, 0, 1);

  // vec2 position;
  // if (gl_VertexID == 0) {
  //   position = node.a;
  // }
  // else if (gl_VertexID == 1) {
  //   position = node.b;
  // }
  // else if (gl_VertexID == 2) {
  //   position = node.b + node.lineWidth;
  // }
  // gl_Position = vec4(position, 0.0f, 1.0f);
  VertexColor = nodes[gl_InstanceID].color;
}
