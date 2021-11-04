#ifndef BEZIER_HEADER
#define BEZIER_HEADER

#include <glm/glm.hpp>
#include <stdlib.h>

using namespace glm;

typedef struct {
  vec2 a;
  vec2 b;
  vec2 p1;
  vec2 p2;
  vec3 color;
} BezierNode;

float makeRandCoord() {
  return (rand() / ((float)RAND_MAX / 2.0f) - 1.0f);
}

BezierNode makeBezierNode() {
  return (BezierNode) {
    .a = vec2(makeRandCoord(), makeRandCoord()),
    .b = vec2(makeRandCoord(), makeRandCoord()),
    .p1 = vec2(makeRandCoord(), makeRandCoord()),
    .p2 = vec2(makeRandCoord(), makeRandCoord()),
    .color = vec3(rand() / (float)RAND_MAX, 
                  rand() / (float)RAND_MAX, 
                  rand() / (float)RAND_MAX)
  };
}

#endif
