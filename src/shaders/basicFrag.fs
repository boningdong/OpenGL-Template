#version 330 core

in vec3 frag_position;
in vec3 frag_normal;
in vec2 frag_texcoords;

out vec4 frag_color;

struct PointLight {
  vec3 position;
  vec3 color;
};

uniform vec3 cam_position;
uniform PointLight light;

// Textures list
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_diffuse2;
uniform sampler2D texture_diffuse3;
uniform sampler2D texture_specular1;
uniform sampler2D texture_specular2;

void main() {
  // TODO: Make the light parameters setable.
  vec3 lightPosition = vec3(0.f, 0.f, 0.f);
  // Light parameters
  vec3 diffuse = vec3(1.0f, 1.0f, 1.0f);
  vec3 ambient = vec3(0.2f, 0.2f, 0.2f);
  vec3 specular = vec3(1.0f, 1.0f, 1.0f);

  // Calculate directions
  vec3 n = normalize(frag_normal);
  vec3 l = normalize(lightPosition - frag_position);
  vec3 v = normalize(cam_position - frag_position);
  vec3 r = reflect(-l, n);

  // Calculate fragments
  vec3 color = vec3(texture(texture_diffuse1, frag_texcoords));
  // vec3 color = vec3(0.3f, 0.4f, 0.6f);
  float shine = pow(max(0, dot(r, v)), 32);
  vec3 d = max(dot(n, l), 0) * diffuse * color;
  vec3 a = ambient * color;
  vec3 s = specular * shine * color;

  // Output
  frag_color = vec4(d + a + s, 1.0f);
  // frag_color = vec4(1.0f, 1.0f, 1.0f, 1.0f);

}
