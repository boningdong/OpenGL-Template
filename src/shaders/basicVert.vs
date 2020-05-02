#version 330 core

// Input vertex attributes
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texcoords;

// Uniforms
// - model: Determines the object location. Need to set a new model parameters before rendering each object.
// - view: Viewport matrix. Depends on the camera.
// - project: projection matrix. Used to project 3d to 2d.
uniform mat4 model;
uniform mat4 view;
uniform mat4 project;

out vec3 frag_position;
out vec3 frag_normal;
out vec2 frag_texcoords;

void main() {
    // Calculate screen space position. (Used to determine which pixel to render on the screen)
    gl_Position = project * view * model * vec4(position, 1.0);

    // Convert a local scope vertex information to be in the world scope.
    frag_position = vec3(model * vec4(position, 1.0));
    frag_normal = mat3(transpose(inverse(model))) * normal;
    frag_texcoords = texcoords;
}