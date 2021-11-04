#ifndef renderer_h
#define renderer_h

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "setup.h"
#include <glm/glm.hpp>
#include "bezier.h"

#define SCR_WIDTH 1080.0
#define SCR_HEIGHT 1080.0

using namespace glm;

typedef struct {
  GLuint program;
  GLuint vbo, vao;
  GLint viewPortUniform;
  GLint colorsUniform;
  GLint nodesUniform;
} RenderProgram;

typedef struct {
  RenderProgram program;
  BezierNode *nodes;
  size_t nodesCount;
} Renderer;

static float vertices[] = {
  -1.0f, -1.0f,
  1.0f, -1.0f,
  1.0f,  1.0f,
};

GLFWwindow *window;

void setupWindow() {
  glfwInit();
	glfwWindowHint(GLFW_SAMPLES, 256);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); 
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(SCR_WIDTH, 
                            SCR_HEIGHT,
                            "OpenGL", 
                            NULL, 
                            NULL);
	glfwMakeContextCurrent(window);
	glewExperimental = 1;
  glewInit();
 	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
 	glEnable( GL_BLEND );

	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
}

static RenderProgram makeProgram() {
  GLuint program = reload_shaders("./shaders/main.vert", "./shaders/main.frag", 0);
  glUseProgram(program);

  GLuint vbo, vao;
  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);
  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);

  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)0);

  GLint viewPortUniform = glGetUniformLocation(program, "viewPort");
  glUniform2iv(viewPortUniform, 1, (int *)&(ivec2(SCR_WIDTH, SCR_HEIGHT)[0]));

  GLint colorsUniform = glGetUniformLocation(program, "colors");
  vec3 colors[] = {
    vec3(1,0,0),
    vec3(0,1,0),
    vec3(0,0,1)
  };
  glUniform3fv(colorsUniform, 3, &(colors[0][0]));

  GLint nodesUniform = glGetUniformLocation(program, "nodes");

  RenderProgram output = {
    .program = program,
    .vbo = vbo,
    .vao = vao,
    .viewPortUniform = viewPortUniform,
    .colorsUniform = colorsUniform,
    .nodesUniform = nodesUniform
  };
  return output;
}

Renderer makeRenderer() {
  RenderProgram p = makeProgram();

  Renderer output = {
    .program = p,
    .nodes = NULL,
    .nodesCount = 0
  };
  return output;
}

void setNodesUniform(GLuint program, BezierNode *nodes, size_t nodesCount) {
  char buffer[64];
  GLint location;
  for (int i = 0; i < (int)nodesCount; i++) {
    sprintf(buffer, "nodes[%d].a", i);
    location = glGetUniformLocation(program, buffer);
    glUniform2fv(location, 1, &(nodes[i].a[0]));

    sprintf(buffer, "nodes[%d].b", i);
    location = glGetUniformLocation(program, buffer);
    glUniform2fv(location, 1, &(nodes[i].b[0]));

    sprintf(buffer, "nodes[%d].p1", i);
    location = glGetUniformLocation(program, buffer);
    glUniform2fv(location, 1, &(nodes[i].p1[0]));

    sprintf(buffer, "nodes[%d].p2", i);
    location = glGetUniformLocation(program, buffer);
    glUniform2fv(location, 1, &(nodes[i].p2[0]));

    sprintf(buffer, "nodes[%d].color", i);
    location = glGetUniformLocation(program, buffer);
    glUniform3fv(location, 1, &(nodes[i].color[0]));
  }
}

void render(Renderer *renderer) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  RenderProgram *program = &renderer->program;
  glUseProgram(program->program);
  glBindVertexArray(program->vao);
  setNodesUniform(program->program, renderer->nodes, renderer->nodesCount);
  glDrawArraysInstanced(GL_TRIANGLES, 
                        0, 
                        sizeof(vertices) / (sizeof(float) * 2), 
                        renderer->nodesCount);

  glfwSwapBuffers(window);
  glfwPollEvents();
}

bool should_close() {
  return glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && 
    glfwWindowShouldClose(window) == 0;
}
#endif
