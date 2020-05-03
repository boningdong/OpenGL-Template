#version 330 core

// Input vertex attributes
layout (location = 0) in vec3 position;

uniform mat4 model;
uniform mat4 view;
uniform mat4 project;

void main() {
    // Calculate screen space position. (Used to determine which pixel to render on the screen)
    gl_Position = project * view * model * vec4(position, 1.0);
}