#pragma once

#include "shader.h"
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <assimp/scene.h>

// Vertex class stores vertex information
struct Vertex {
  glm::vec3 position;
  glm::vec3 normal;
  glm::vec2 texCoords;
};

// Texture class stores the id of the texture loaded into the GRAM
struct Texture {
  unsigned int id;
  std::string type;
  std::string path; // need this because we want to compare strings to see if we are trying to load the same texture.
};

// Mesh class stores the information of a mesh
class Mesh {
public:
  unsigned int vao;
  std::vector<Vertex> vertices;
  std::vector<unsigned int> indices;
  std::vector<Texture> textures;
  Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
  void draw(Shader *shader);
private:
  unsigned int vbo, ebo;
  void setupMesh();
};


