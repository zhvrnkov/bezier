#version 430 core

struct BezierNode {
  vec2 a;
  vec2 b;
  vec2 p1;
  vec2 p2;
  vec3 color;
  float lineWidth;
  float unused[1];
};

layout (location = 0) in vec2 aPos;

uniform int elementsPerInstance;
uniform BezierNode nodes[200];
uniform vec3 colors[3];

out vec3 VertexColor;

float lerp(float a, float b, float t) {
  return a + (b - a) * t;
}

float a(float x, BezierNode node) {
  float p0 = node.a.y;
  float p1 = node.p1.y;
  return lerp(p0, p1, x);
}

float b(float x, BezierNode node) {
  float p1 = node.p1.y;
  float p2 = node.b.y;
  return lerp(p1, p2, x);
}

vec2 point(float t, BezierNode node) {
  float q0 = node.a.x;
  float q1 = node.p1.x;
  float q2 = node.b.x;
  float d0_1 = lerp(q0, q1, t);
  float d1_2 = lerp(q1, q2, t);
  float x = lerp(d0_1, d1_2, t);
  float y = lerp(a(t, node), b(t, node), ((x - d0_1) / (d1_2 - d0_1)));
  return vec2(x, y);
}

void main() {
  BezierNode node = nodes[gl_InstanceID];
  
  float t = float(gl_VertexID / 2) / float(elementsPerInstance / 2);
  vec2 p = point(t, node);
  vec2 bFromA = node.b - node.a;
  vec2 instanceStep = bFromA / float(elementsPerInstance / 2);
  vec2 elementBase = node.a + (float(gl_VertexID / 2) * instanceStep);
  float length = node.lineWidth * (float(gl_VertexID % 2) - 0.5);
  vec2 tangent = normalize(vec2(-bFromA.y, bFromA.x));
  gl_Position = vec4(p + (tangent * length), 0, 1);
  VertexColor = nodes[gl_InstanceID].color;
}
