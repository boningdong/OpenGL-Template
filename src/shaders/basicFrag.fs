#version 330 core

in vec3 frag_position;
in vec3 frag_normal;
in vec2 frag_texcoords;

out vec4 frag_color;

struct PointLight {
  vec3 position;
  vec3 color;
};

uniform vec3 camera_position;
uniform PointLight light;

// Textures list
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_diffuse2;
uniform sampler2D texture_specular1;
uniform sampler2D texture_specular2;
uniform sampler2D texture_normal1;
uniform sampler2D texture_normal2;

void main() {
  // TODO: Make the light parameters setable.
  // Light parameters
  vec3 diffuse = light.color;
  vec3 specular = light.color;
  vec3 ambient = light.color * 0.1f;

  // Calculate directions
  vec3 normal_texel = vec3(texture(texture_normal1, frag_texcoords));
  vec3 n = normalize(frag_normal);
  vec3 l = normalize(light.position - frag_position);
  vec3 v = normalize(camera_position - frag_position);
  vec3 r = reflect(-l, n);

  // Calculate fragments
  vec3 diffuse_texel = vec3(texture(texture_diffuse1, frag_texcoords));
  vec3 specular_texel = vec3(texture(texture_specular1, frag_texcoords));
  float shine = pow(max(0, dot(r, v)), 32);
  vec3 d = max(dot(n, l), 0) * diffuse * diffuse_texel;
  vec3 a = ambient * light.color;
  vec3 s = specular * shine * specular_texel;

  // Output
  frag_color = vec4(d + a + s, 1.0f);
}
