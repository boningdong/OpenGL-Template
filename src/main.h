#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "shader.h"
#include "model.h"
#include "camera.h"
#include <iostream>
#include <string>
#include <sstream>
#include <glm/gtc/matrix_transform.hpp>

void processUserInput(GLFWwindow * window);
void cursorMoveCallback(GLFWwindow* window, double xpos, double ypos);
void framebufferResizeCallback(GLFWwindow * window, int width, int height);
