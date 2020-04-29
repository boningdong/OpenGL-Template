#pragma once

#include <glm/glm.hpp>
#include <string>

typedef unsigned int ShaderId;

class Shader {
public:
  // initializes a shader from GLSL source files
  Shader(const char* vertex_path, const char* fragment_path);

  // set as active shadser
  void use(void);
  // retrieve shader glfw id
  ShaderId getId(void) const;
  // assign a global variable of type int in shader
  void setInt(const std::string& name, int value) const;
  // assign a global variable of type float in shader
  void setFloat(const std::string& name, float value) const;
  // assign a global variable of type bool in shader
  void setBool(const std::string& name, bool value) const;
  // assign a global vectors/matrices
  void setVec2(const std::string& name, const glm::vec2& value) const;
  void setVec2(const std::string& name, float x, float y) const;
  void setVec3(const std::string& name, const glm::vec3& value) const;
  void setVec3(const std::string& name, float x, float y, float z) const;
  void setVec4(const std::string& name, const glm::vec4& value) const;
  void setVec4(const std::string& name, float x, float y, float z, float w) const;
  void setMat2(const std::string& name, const glm::mat2& mat) const;
  void setMat3(const std::string& name, const glm::mat3& mat) const;
  void setMat4(const std::string& name, const glm::mat4& mat) const;

private:
  ShaderId shaderId = 0;
};