#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <iostream>

int main() {
  // NOTE: About shader folder
  // SHADER_FOLDER is defined in CMakeList.txt under this folder
  std::cout << SHADER_FOLDER << std::endl;

  GLFWwindow* window;
  
  // Initialize the library
  if (!glfwInit())
    return -1;
  
  // Check OpenGL version
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  #ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  #endif
  
  // Create a windowed mode window and its OpenGL context
  window = glfwCreateWindow(640, 480, "template", NULL, NULL);
  if (!window) {
    glfwTerminate();
    return -1;
  }

  // Make the window's context current
  glfwMakeContextCurrent(window);

  // Initialize glad
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize glad." << std::endl;
    exit(1);
  }

  // Main render loop
  while (!glfwWindowShouldClose(window)) {
    // Render here
    glClear(GL_COLOR_BUFFER_BIT);
    
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}