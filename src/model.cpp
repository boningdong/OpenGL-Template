
// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on

#include "model.h"
#include "stb_image.h"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include "model.h"

// Model class
void Model::draw(glm::vec3 &pos, glm::vec3 &scale, Camera &camera) {
  shader->use();

  // Update camera location
  glm::mat4 project =  glm::mat4(1.f);
  glm::mat4 view = glm::mat4(1.f);
  project = glm::perspective(glm::radians(camera.fov), camera.aspect, 0.1f, 100.f);
  view = glm::lookAt(camera.pos, camera.pos + camera.dir, camera.WORLD_UP);
  shader->setMat4("project", project);
  shader->setMat4("view", view);
  shader->setVec3("camera_position", camera.pos);

  // Set the model matrix before rendering the model.
  glm::mat4 model = glm::mat4(1.f);
  model = glm::translate(model, pos);
  model = glm::scale(model, scale);
  shader->setMat4("model", model);
  for (int i = 0; i < this->meshes.size(); i++) {
    meshes[i].draw(shader);
  }
}

void Model::loadModel(std::string path) {
  Assimp::Importer importer;
  std::cout << "Loading model: " << path << std::endl;
  const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
  if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
    std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
    return;
  }
  directory = path.substr(0, path.find_last_of("/\\"));
  processNode(scene->mRootNode, scene);
  
  // Log model information
  int diffuseCounts = 0;
  int specularCounts = 0;
  int normalCounts = 0;
  for (auto texture : textures_loaded) {
    if (texture.type == "texture_diffuse")
      diffuseCounts ++;
    else if (texture.type == "texture_specular")
      specularCounts ++;
    else if (texture.type == "texture_normal")
      normalCounts ++;
  }
  std::cout << "Done loading node. Diffuse " << diffuseCounts << " Specular " << specularCounts << " Normal: " << normalCounts << std::endl;
}

void Model::processNode(aiNode* node, const aiScene* scene) {
  for (unsigned int i = 0; i < node->mNumMeshes; i++) {
    aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
    meshes.push_back(processMesh(mesh, scene));
  }
  for (unsigned int i = 0; i < node->mNumChildren; i++) {
    processNode(node->mChildren[i], scene);
  }
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene) {
  std::vector<Vertex> vertices;
  std::vector<unsigned int> indices;
  std::vector<Texture> textures;

  // process vertices
  for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
    Vertex vertex;
    glm::vec3 v3;
    v3.x = mesh->mVertices[i].x;
    v3.y = mesh->mVertices[i].y;
    v3.z = mesh->mVertices[i].z;
    vertex.position = v3;

    v3.x = mesh->mNormals[i].x;
    v3.y = mesh->mNormals[i].y;
    v3.z = mesh->mNormals[i].z;
    vertex.normal = v3;

    if (mesh->mTextureCoords[0]) {
      glm::vec2 v2;
      v2.x = mesh->mTextureCoords[0][i].x;
      v2.y = mesh->mTextureCoords[0][i].y;
      vertex.texCoords = v2;
    } else {
      vertex.texCoords = glm::vec2(0.0f, 0.0f);
    }
    vertices.push_back(vertex);
  }

  // process indices
  for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
    aiFace face = mesh->mFaces[i];
    for (unsigned int j = 0; j < face.mNumIndices; j++) {
      indices.push_back(face.mIndices[j]);
    }
  }

  // process material
  if (mesh->mMaterialIndex >= 0) {
    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
    // load diffuse map
    std::vector<Texture> diffuseMaps =
      loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    // load specular map
    std::vector<Texture> specularMaps =
      loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    // load normal map
    std::vector<Texture> normalMaps =
      loadMaterialTextures(material, aiTextureType_NORMAL_CAMERA, "texture_normal");
    textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
  }
  return Mesh(vertices, indices, textures);
}

unsigned int textureFromFile(const char* path, const std::string& directory) {
  std::string filename = std::string(path);
  filename = directory + '/' + filename;
  std::replace(filename.begin(), filename.end(), '\\', '/');
  unsigned int texture_id;
  glGenTextures(1, &texture_id);
  int width, height, channels;
  unsigned char* data = stbi_load(filename.c_str(), &width, &height, &channels, 0);
  if (data) {
    // Determine the texture format
    GLenum format;
    if (channels == 1)
      format = GL_ALPHA;
    else if (channels == 3)
      format = GL_RGB;
    else if (channels == 4)
      format = GL_RGBA;
    // Generate and store the texture
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    stbi_image_free(data);
  } else {
    std::cout << "Texture failed to load at path: " << filename << std::endl;
    stbi_image_free(data);
  }
  return texture_id;
}

std::vector<Texture>
  Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName) {
  std::vector<Texture> textures;
  for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
    aiString str;
    mat->GetTexture(type, i, &str);
    // Check if texture is already loaded
    bool skip = false;
    for (unsigned int j = 0; j < textures_loaded.size(); j++) {
      if (std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0) {
        textures.push_back(textures_loaded[j]);
        skip = true;
        break;
      }
    }
    // Load the texture if it's not loaded
    if (!skip) {
      Texture texture;
      texture.id = textureFromFile(str.C_Str(), directory);
      texture.type = typeName;
      texture.path = str.C_Str();
      textures.push_back(texture);
      textures_loaded.push_back(texture);
    }
  }
  return textures;
}
