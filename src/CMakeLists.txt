cmake_minimum_required(VERSION 2.8)

# set source files
set(APPLICATION_SOURCE
  main.cpp
  mesh.cpp
  model.cpp
  shader.cpp
)

# set executable output path
set(EXECUTABLE_OUTPUT_PATH ..)

# add executable file
add_executable(template ${APPLICATION_SOURCE})

# link libarires
target_link_libraries(template
  glfw
  glad
  glm
  stb
  assimp
)

# include
target_include_directories(template PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# deinitions
# target_compile_definitions(template PUBLIC SHADER_FOLDER="${CMAKE_CURRENT_SOURCE_DIR}/shaders")
add_definitions(SHADER_FOLDER="${CMAKE_CURRENT_SOURCE_DIR}/shaders")
