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
  vec2 instanceStep = bFromA / float(elementsPerInstance);
  vec2 elementBase = node.a + (float(gl_VertexID / 2) * instanceStep);
  float length = node.lineWidth * (float(gl_VertexID % 2) - 0.5);
  vec2 tangent = normalize(vec2(-bFromA.y, bFromA.x));
  gl_Position = vec4(elementBase + (tangent * length) + instanceStep, 0, 1);
  VertexColor = nodes[gl_InstanceID].color;
}
