#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include "shader.h"

class PointLight {
public:
  glm::vec3 pos;
  glm::vec3 color;
  float intensity;
  int dir;
  float speed;
  PointLight(const glm::vec3 pos, const glm::vec3 color, float intensity, int dir, float speed);
  void draw(const glm::mat4& projection, const glm::mat4& view);

private:
  static unsigned int vao, vbo, ebo;
  static void setupLight();
  static Shader* shader;
};