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
  const char *vertSource = vertSourceCode.c_str();
  const char *fragSource = fragSourceCode.c_str();

  // Compile the loaded vertex shader
  int vertShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertShader, 1, &vertSource, NULL);
  glCompileShader(vertShader);
  glGetShaderiv(vertShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertShader, sizeof(log), NULL, log);
    std::cout << "Failed to compile vertex shader:\n" << log << std::endl;
  }

  // Compile the loaded fragment shader
  int fragShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragShader, 1, &fragSource, NULL);
  glCompileShader(fragShader);
  glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragShader, sizeof(log), NULL, log);
    std::cout << "Failed to compile fragment shader:\n" << log << std::endl;
  }

  // Link the vertex and fragment shader to from a pipeline
  shaderId = glCreateProgram();
  glAttachShader(shaderId, vertShader);
  glAttachShader(shaderId, fragShader);
  glLinkProgram(shaderId);
  glGetProgramiv(shaderId, GL_LINK_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(shaderId, sizeof(log), NULL, log);
    std::cout << "Failed to link shaders:\n" << log << std::endl;
    std::cout << "GLGetError: " << glGetError() << std::endl;
  }
  std::cout << "Shader loaded successfully!" << std::endl;
  glDeleteShader(vertShader);
  glDeleteShader(fragShader);
}

void Shader::use() { glUseProgram(shaderId);}

ShaderId Shader::getId(void) const { return shaderId; }

// Methods used to configure uniform attributes in shader programs
void Shader::setInt(const std::string &name, int value) const {
  glUseProgram(shaderId);
  glUniform1i(glGetUniformLocation(shaderId, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const {
  glUseProgram(shaderId);
  glUniform1f(glGetUniformLocation(shaderId, name.c_str()), value);
}

void Shader::setBool(const std::string &name, bool value) const {
  glUseProgram(shaderId);
  setInt(name, (int)value);
}

void Shader::setVec2(const std::string &name, const glm::vec2 &value) const {
  glUseProgram(shaderId);
  glUniform2fv(glGetUniformLocation(shaderId, name.c_str()), 1, &value[0]);
}

void Shader::setVec2(const std::string &name, float x, float y) const {
  glUseProgram(shaderId);
  glUniform2f(glGetUniformLocation(shaderId, name.c_str()), x, y);
}

void Shader::setVec3(const std::string &name, const glm::vec3 &value) const {
  glUseProgram(shaderId);
  glUniform3fv(glGetUniformLocation(shaderId, name.c_str()), 1, &value[0]);
}

void Shader::setVec3(const std::string &name, float x, float y, float z) const {
  glUseProgram(shaderId);
  glUniform3f(glGetUniformLocation(shaderId, name.c_str()), x, y, z);
}

void Shader::setVec4(const std::string &name, const glm::vec4 &value) const {
  glUseProgram(shaderId);
  glUniform4fv(glGetUniformLocation(shaderId, name.c_str()), 1, &value[0]);
}

void Shader::setVec4(const std::string &name, float x, float y, float z,
                     float w) const {
  glUseProgram(shaderId);
  glUniform4f(glGetUniformLocation(shaderId, name.c_str()), x, y, z, w);
}

void Shader::setMat2(const std::string &name, const glm::mat2 &mat) const {
  glUseProgram(shaderId);
  glUniformMatrix2fv(glGetUniformLocation(shaderId, name.c_str()), 1, GL_FALSE,
                     &mat[0][0]);
}

void Shader::setMat3(const std::string &name, const glm::mat3 &mat) const {
  glUseProgram(shaderId);
  glUniformMatrix3fv(glGetUniformLocation(shaderId, name.c_str()), 1, GL_FALSE,
                     &mat[0][0]);
}

void Shader::setMat4(const std::string &name, const glm::mat4 &mat) const {
  glUseProgram(shaderId);
  glUniformMatrix4fv(glGetUniformLocation(shaderId, name.c_str()), 1, GL_FALSE,
                     &mat[0][0]);
}