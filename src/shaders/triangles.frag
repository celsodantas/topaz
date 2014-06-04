#version 330

in  vec3 normal;
out vec3 color;

void main()
{
  // Output color = red 
  // color = vec3(0,1,0);
  color = normal;
}