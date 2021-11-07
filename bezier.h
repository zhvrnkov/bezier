#ifndef BEZIER_HEADER
#define BEZIER_HEADER

#include <glm/glm.hpp>
#include <stdlib.h>

#define ANIMATION_SPEED 0.001

using namespace glm;

typedef struct {
  vec2 a;
  vec2 b;
  vec2 p1;
  vec2 p2;
  vec3 color;
  float lineWidth;

  vec2 p1Speed;
  vec2 p2Speed;

  float animationSpeed;
} BezierNode;

float makeRandCoord() {
  return (rand() / ((float)RAND_MAX / 2.0f) - 1.0f);
}

float makeRandSpeed(float animationSpeed) {
  return ((rand() / ((float)RAND_MAX / 2.0f) - 1.0f)) * animationSpeed;
} 

BezierNode makeBezierNode() {
  return (BezierNode) {
    .a = vec2(makeRandCoord(), makeRandCoord()),
    .b = vec2(makeRandCoord(), makeRandCoord()),
    .p1 = vec2(makeRandCoord(), makeRandCoord()),
    .p2 = vec2(makeRandCoord(), makeRandCoord()),
    .color = vec3(rand() / (float)RAND_MAX, 
                  rand() / (float)RAND_MAX, 
                  rand() / (float)RAND_MAX),
    .lineWidth = 0.02,
    .p1Speed = vec2(makeRandSpeed(ANIMATION_SPEED), makeRandSpeed(ANIMATION_SPEED)),
    .p2Speed = vec2(makeRandSpeed(ANIMATION_SPEED), makeRandSpeed(ANIMATION_SPEED)),
    .animationSpeed = ANIMATION_SPEED
  };
}

vec2 animatedVector(vec2 source, vec2 *speed) {
  if (source.x >= 1.0 || source.x <= -1.0)
    speed->x = -speed->x;
  if (source.y >= 1.0 || source.y <= -1.0)
    speed->y = -speed->y;
  return source + *speed;
}

void animate(BezierNode *node) {
  node->p1 = animatedVector(node->p1, &(node->p1Speed));
  node->p2 = animatedVector(node->p2, &(node->p2Speed));
}

#endif
