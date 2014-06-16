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
  Cursor cursor = engine.cursor;

  if (cursor.btn1Pressed)
  {
    updateRotation(cursor, engine.deltaTime);
  }

  if (cursor.btn2Pressed)
  {
    updateTranslation(cursor, engine.deltaTime);
  }
}

void Topaz::Engine::Camera::updateRotation(Cursor &cursor, float deltaTime)
{
  float rotationSpeed = 0.1f;
  float xAngle = cursor.deltaX * rotationSpeed * deltaTime;
  float yAngle = cursor.deltaY * rotationSpeed * deltaTime;

  glm::quat quat_destin(glm::vec3(yAngle, 0.f, xAngle));

  matrix = matrix * glm::toMat4(quat_destin);
}

void Topaz::Engine::Camera::updateTranslation(Cursor &cursor, float deltaTime)
{
  float translationSpeed = 0.1f;
  float x = cursor.deltaX * translationSpeed * deltaTime;
  float y = cursor.deltaY * translationSpeed * deltaTime;

  matrix = glm::translate(matrix, glm::vec3(x, y, 0));
}
