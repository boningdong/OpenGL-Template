#pragma once

#include <glm/glm.hpp>
#include "camera.h"
#include "model.h"
#include "lights.h"

class Object {
public:
  glm::vec3 pos;
  glm::vec3 scale;
  Model *model;
  Object (glm::vec3 pos, glm::vec3 scale, Model *model) : pos(pos), scale(scale), model(model) {};
  void draw(Camera &camera, PointLight& light);
private:
};