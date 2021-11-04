#version 430 core

struct BezierNode {
  vec2 a;
  vec2 b;
  vec2 p1;
  vec2 p2;
  vec3 color;
};

layout (location = 0) in vec2 aPos;

uniform BezierNode nodes[200];
uniform vec3 colors[3];

out vec3 VertexColor;

void main() {
  if (aPos.x == 1.0f && aPos.y == -1.0f) {
    if ((gl_InstanceID + 1) % 2 == 0) {
      gl_Position = vec4(-1,1,0,1);
    }
    else {
      gl_Position = vec4(1.0f,-1.0f,0.0f,1.0f);
    }
  }
  else {
    gl_Position = vec4(aPos, 0, 1);
  }
  VertexColor = nodes[gl_InstanceID].color;
}
