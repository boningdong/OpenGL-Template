#pragma once

#include "mesh.h"
#include "shader.h"
#include "camera.h"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <vector>

class Model {
public:
  std::vector<Texture> textures_loaded;
  std::vector<Mesh> meshes;
  std::string directory;
  Shader *shader;
  Model() {}
  Model(const char *path, Shader* shader) : shader(shader) {
    std::cout << "Actual path: " << path << std::endl;
    loadModel(path);
  }
  void draw(glm::vec3 &pos, glm::vec3 &scale, Camera &camera);

private:
  void loadModel(std::string path);
  void processNode(aiNode *node, const aiScene *scene);
  Mesh processMesh(aiMesh *mesh, const aiScene *scene);
  std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type,
                                            std::string typeName);
};
