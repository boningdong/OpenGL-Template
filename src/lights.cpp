#include "lights.h"

// static members declaration
glm::vec3 PointLight::scale(0.2f, 0.2f, 0.2f);
Shader* PointLight::shader = nullptr;
Model* PointLight::model = nullptr;


PointLight::PointLight(glm::vec3 pos, glm::vec3 color, float intensity) {
  this->pos = pos;
  this->color = color;
  this->intensity = intensity;
}

PointLight::~PointLight() {
  if (shader != nullptr)
    delete shader;
  if (model != nullptr)
    delete model;
}

void PointLight::enableRendering() {
  if (model != nullptr)
    return;
  std::stringstream ssVert, ssFrag;
  ssVert << SHADER_FOLDER << "pointLight.vs";
  ssFrag << SHADER_FOLDER << "pointLight.fs";
  PointLight::shader = new Shader(ssVert.str().c_str(), ssFrag.str().c_str());

  std::stringstream ssModel;
  ssModel << MODEL_FOLDER << "sphere.obj";
  PointLight::model = new Model(ssModel.str().c_str(), shader);
}

void PointLight::draw(Camera &camera) {
  if (shader == nullptr || model == nullptr) {
    std::cout << "Point light rendering is not enabled." << std::endl;
    return;
  }
  PointLight::shader->setVec3("color", color);
  PointLight::model->draw(pos, scale, camera);
}