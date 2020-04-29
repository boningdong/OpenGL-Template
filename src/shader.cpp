#include "shader.h"

#include <fstream>
#include <glad/glad.h>
#include <iostream>
#include <sstream>

Shader::Shader(const char *vertPath, const char *fragPath) {
  std::string vertSourceCode;
  std::string fragSourceCode;
  std::ifstream vertFile;
  std::ifstream fragFile;

  vertFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  fragFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  try {
    // Open shader files
    vertFile.open(vertPath);
    fragFile.open(fragPath);
    // Read into string streams
    std::stringstream vertex_stream, fragment_stream;
    vertex_stream << vertFile.rdbuf();
    fragment_stream << fragFile.rdbuf();
    // Close files
    vertFile.close();
    fragFile.close();
    // Save source code into strings
    vertSourceCode = vertex_stream.str();
    fragSourceCode = fragment_stream.str();
  } catch (std::ifstream::failure e) {
    std::cout << "Failed to read shader sources" << std::endl;
  }

  int success;
  char log[512];
  const char *vSourceStr = vertSourceCode.c_str();
  const char *fSourceStr = fragSourceCode.c_str();

  // Compile the loaded vertex shader
  int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vSourceStr, NULL);
  glCompileShader(vertexShader);
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertexShader, sizeof(log), NULL, log);
    std::cout << "Failed to compile vertex shader:\n" << log << std::endl;
  }

  // Compile the loaded fragment shader
  int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fSourceStr, NULL);
  glCompileShader(fragmentShader);
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragmentShader, sizeof(log), NULL, log);
    std::cout << "Failed to compile fragment shader:\n" << log << std::endl;
  }

  // Link the vertex and fragment shader to from a pipeline
  shaderId = glCreateProgram();
  glAttachShader(shaderId, vertexShader);
  glAttachShader(shaderId, fragmentShader);
  glLinkProgram(shaderId);
  glGetProgramiv(shaderId, GL_LINK_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(shaderId, sizeof(log), NULL, log);
    std::cout << "Failed to link shaders:\n" << log << std::endl;
  }

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}

void Shader::use() { glUseProgram(shaderId); }

ShaderId Shader::getId(void) const { return shaderId; }

// Methods used to configure uniform attributes in shader programs
void Shader::setInt(const std::string &name, int value) const {
  glUniform1i(glGetUniformLocation(shaderId, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const {
  glUniform1f(glGetUniformLocation(shaderId, name.c_str()), value);
}

void Shader::setBool(const std::string &name, bool value) const {
  setInt(name, (int)value);
}

void Shader::setVec2(const std::string &name, const glm::vec2 &value) const {
  glUniform2fv(glGetUniformLocation(shaderId, name.c_str()), 1, &value[0]);
}

void Shader::setVec2(const std::string &name, float x, float y) const {
  glUniform2f(glGetUniformLocation(shaderId, name.c_str()), x, y);
}

void Shader::setVec3(const std::string &name, const glm::vec3 &value) const {
  glUniform3fv(glGetUniformLocation(shaderId, name.c_str()), 1, &value[0]);
}

void Shader::setVec3(const std::string &name, float x, float y, float z) const {
  glUniform3f(glGetUniformLocation(shaderId, name.c_str()), x, y, z);
}

void Shader::setVec4(const std::string &name, const glm::vec4 &value) const {
  glUniform4fv(glGetUniformLocation(shaderId, name.c_str()), 1, &value[0]);
}

void Shader::setVec4(const std::string &name, float x, float y, float z,
                     float w) const {
  glUniform4f(glGetUniformLocation(shaderId, name.c_str()), x, y, z, w);
}

void Shader::setMat2(const std::string &name, const glm::mat2 &mat) const {
  glUniformMatrix2fv(glGetUniformLocation(shaderId, name.c_str()), 1, GL_FALSE,
                     &mat[0][0]);
}

void Shader::setMat3(const std::string &name, const glm::mat3 &mat) const {
  glUniformMatrix3fv(glGetUniformLocation(shaderId, name.c_str()), 1, GL_FALSE,
                     &mat[0][0]);
}

void Shader::setMat4(const std::string &name, const glm::mat4 &mat) const {
  glUniformMatrix4fv(glGetUniformLocation(shaderId, name.c_str()), 1, GL_FALSE,
                     &mat[0][0]);
}