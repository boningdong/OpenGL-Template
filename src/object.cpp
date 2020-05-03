#include "object.h"

void Object::draw(Camera &camera, PointLight &light) {
  model->shader->setVec3("light.color", light.color);
  model->shader->setVec3("light.position", light.pos);
  model->draw(pos, scale, camera);
}