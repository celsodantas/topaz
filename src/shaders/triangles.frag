#version 330

in  vec3 normal;
out vec3 color;

void main()
{
  // Adding a little bit of colour so we don't get true black
  // This is just for testing
  color = normal + vec3(0.1f, 0.1f, 0.1f);
}
