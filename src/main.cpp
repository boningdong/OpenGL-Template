
#include "main.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

// Global variables
Camera camera = Camera(
  glm::vec3(15.f, 15.f, 20.f), 
  glm::vec3(-0.6f -0.3f -0.8f), 
  WINDOW_WIDTH, WINDOW_HEIGHT);

float dt, tt = 0;

int main() {
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
  GLFWwindow *window;
  window =
      glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "template", NULL, NULL);
  if (!window) {
    glfwTerminate();
    return -1;
  }
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  // Make the window's context current
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
  glfwSetCursorPosCallback(window, cursorMoveCallback);

  // Initialize glad
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize glad." << std::endl;
    exit(1);
  }

  // glEnable(GL_DEPTH_TEST);

  // World components
  // NOTE: Load shader
  std::stringstream ssVertPath, ssFragPath;
  ssVertPath << SHADER_FOLDER << "basicVert.vs";
  ssFragPath << SHADER_FOLDER << "basicFrag.fs";
  Shader shader = Shader(ssVertPath.str().c_str(), ssFragPath.str().c_str());

  // NOTE: Load model
  std::stringstream ssModelPath;
  ssModelPath << MODEL_FOLDER << "nanosuit/nanosuit.obj";
  Model object = Model(ssModelPath.str().c_str());

  // Main render loop
  while (!glfwWindowShouldClose(window)) {
    float t = glfwGetTime();
    dt = tt == 0 ? 0 : t - tt;
    tt = t;

    processUserInput(window);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Render Start
    // NOTE: Set the view transport parameters
    camera.update(shader);
    // NOTE: Start rendering
    object.draw(shader);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}

void processUserInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
    camera.pos += camera.dir * camera.speed * dt;
  }
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
    camera.pos -= camera.dir * camera.speed * dt;
  }
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
    // Move in the direction orthogonal to the camera direction and up vector
    camera.pos += glm::normalize(glm::cross(camera.dir, camera.WORLD_UP)) * camera.speed * dt;
  }
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
    // Move in the direction orthogonal to the camera direction and up vector
    camera.pos -= glm::normalize(glm::cross(camera.dir, camera.WORLD_UP)) * camera.speed * dt;
  }
  if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
    // Log camera information
    std::cout << "Camera position: " << camera.pos.r << " " << camera.pos.g << " " << camera.pos.b << std::endl;
    std::cout << "Camera direction: " << camera.dir.r << " " << camera.dir.g << " " << camera.dir.b << std::endl;
  }
}

void cursorMoveCallback(GLFWwindow* window, double xpos, double ypos) {
  static int xprev = xpos;
  static int yprev = ypos;

  camera.yaw += (xpos - xprev) * camera.sense;
  camera.pitch += (yprev - ypos) * camera.sense; // invert y since 0 == top
  xprev = xpos;
  yprev = ypos;

  if (camera.pitch < -89.f)
    camera.pitch = CAM_PITCH_MIN;
  else if (camera.pitch > CAM_PITCH_MAX)
    camera.pitch = CAM_PITCH_MAX;

  // calculate direction from geometry
  camera.dir = glm::normalize(glm::vec3(
    cos(glm::radians(camera.yaw)) * cos(glm::radians(camera.pitch)),
    sin(glm::radians(camera.pitch)),
    sin(glm::radians(camera.yaw)) * cos(glm::radians(camera.pitch))));
}

void framebufferResizeCallback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}
