#include "Camera.hpp"
#include "Core.hpp"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

Topaz::Engine::Camera::Camera()
{
  // Static location for now
  matrix = glm::lookAt(
      glm::vec3(0 , -2, 0), // Camera position, in World Space
      glm::vec3(0,  0,  0), // and looks at
      glm::vec3(0,  0,  1)  // Head is up (set to 0,-1,0 to look upside-down)
  );
}

void Topaz::Engine::Camera::tick(Engine::Core engine)
{
  // Rotating camera to follow cursor

  Cursor cursor = engine.cursor;
  float rotationSpeed = 0.1f;
  float xAngle = engine.cursor.deltaX * rotationSpeed * engine.deltaTime;
  float yAngle = engine.cursor.deltaY * rotationSpeed * engine.deltaTime;

  glm::quat quat_destin(glm::vec3(yAngle, 0.f, xAngle));

  matrix = matrix * glm::toMat4(quat_destin);
}
