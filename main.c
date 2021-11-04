#include <glm/glm.hpp>
#include <math.h>
#include "renderer.h"
#include "bezier.h"

Renderer unitsRenderer;

int main() {
  setupWindow();
  unitsRenderer = makeRenderer();
  BezierNode nodes[200];
  unitsRenderer.nodesCount = 200;
  unitsRenderer.nodes = nodes;
  for (int i = 0; i < 200; i++)
    unitsRenderer.nodes[i] = makeBezierNode();

  for (size_t i = 0; should_close(); i++) {
    render(&unitsRenderer);
  }

  glfwTerminate();
  return 0;
}
