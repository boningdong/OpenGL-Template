#pragma once

#include "shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define CAM_PITCH_MAX 89.0f
#define CAM_PITCH_MIN -89.0f

class Camera {
public:
  glm::vec3 pos;
  glm::vec3 dir;
  float fov;
  float aspect;
  float pitch = 0, yaw = -90;
  const glm::vec3 WORLD_UP = glm::vec3(0, 1, 0);

  float speed = 5.0f;
  float sense = 0.05f;

  Camera(glm::vec3 pos, glm::vec3 dir, float width, float height,
         float fov = 45)
      : pos(pos), dir(dir), fov(fov) {
    aspect = width / height;
  }
  void update(Shader &shader);
};