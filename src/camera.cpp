#include "camera.h"

void Camera::update(Shader &shader) {
  glm::mat4 project =  glm::mat4(1.f);
  glm::mat4 view = glm::mat4(1.f);
  project = glm::perspective(glm::radians(fov), aspect, 0.1f, 100.f);
  view = glm::lookAt(pos, pos + dir, WORLD_UP);
  shader.setMat4("project", project);
  shader.setMat4("view", view);
}