#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include <sstream>
#include "shader.h"
#include "model.h"
#include "camera.h"
#include "string"

class PointLight {
public:
  glm::vec3 pos;
  glm::vec3 color;
  float intensity;
  PointLight(glm::vec3 pos, glm::vec3 color, float intensity);
  ~PointLight();
  void draw(Camera &camera);
  static void enableRendering();
private:
  static glm::vec3 scale;
  static Shader *shader;
  static Model *model;
};