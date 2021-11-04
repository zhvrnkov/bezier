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
  vec2 position;
  if (gl_VertexID == 0) {
    position = node.a;
  }
  else if (gl_VertexID == 1) {
    position = node.b;
  }
  else if (gl_VertexID == 2) {
    position = node.b + node.lineWidth;
  }
  // if (aPos.x == 1.0f && aPos.y == -1.0f) {
  //   if ((gl_InstanceID + 1) % 2 == 0) {
  //     gl_Position = vec4(-1,1,0,1);
  //   }
  //   else {
  //     gl_Position = vec4(1.0f,-1.0f,0.0f,1.0f);
  //   }
  // }
  // else {
  //   gl_Position = vec4(aPos, 0, 1);
  // }
  gl_Position = vec4(position, 0.0f, 1.0f);
  VertexColor = nodes[gl_InstanceID].color;
}
