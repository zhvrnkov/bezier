#include <glm/glm.hpp>
#include <math.h>
#include "renderer.h"
#include "bezier.h"

using namespace glm;

Renderer unitsRenderer;

int main() {
  setupWindow();
  unitsRenderer = makeRenderer();
  int nodesCount = 200;
  BezierNode nodes[nodesCount];
  unitsRenderer.nodesCount = nodesCount;
  unitsRenderer.nodes = nodes;
  for (int i = 0; i < nodesCount; i++) {
    /* BezierNode node = makeBezierNode(); */
    /* node.a = vec2(-1.0f, -1.0f); */
    /* node.b = vec2(1.0f, 1.0f); */
    /* node.p1 = vec2(0, 0.5); */
    /* node.color = vec3(1.0, 0.0, 0.0); */
    /* node.lineWidth = 0.02; */
    /* unitsRenderer.nodes[i] = node; */
    unitsRenderer.nodes[i] = makeBezierNode();
  }

  for (size_t i = 0; should_close(); i++) {
    for (int index = 0; index < nodesCount; index++) {
      animate(&(unitsRenderer.nodes[index]));
    }
    render(&unitsRenderer);
  }

  glfwTerminate();
  return 0;
}
