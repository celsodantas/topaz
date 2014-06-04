#version 330
in vec3 vertex_position;
in vec3 vertex_normal;
// in vec3 vertex_colour;

uniform mat4 matrix;
out vec3 normal;

void main () {
  // colour = vertex_colour;
  normal = vertex_normal;
  gl_Position = matrix * vec4(vertex_position, 1.0);
}