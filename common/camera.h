#ifndef CAMERA_H
#define CAMERA_H

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <common/gameobject.h>

class Camera {
  public:
    Camera();
    virtual ~Camera();

    void computeMatricesFromInputs(GLFWwindow* window);
    void computeMatricesFromInputs(GLFWwindow* window, glm::vec3 newPos);
    glm::mat4 getViewMatrix() {return ViewMatrix; };
    glm::mat4 getProjectionMatrix() {return ProjectionMatrix; };
    glm::vec3 getCursor() {return cursor; };

    void parent(Gameobject* newParent) {_parent = newParent; };
    Gameobject* parent() {return _parent; };

    glm::vec3 localPosition() { return _localPosition; };
    void localPosition(glm::vec3 newPos) { _localPosition = newPos; };

   float deltaTime(){return _deltaTime; };

private:

  glm::mat4 ViewMatrix;
  glm::mat4 ProjectionMatrix;

	float horizontalAngle;
	float verticalAngle;
	float initialFoV;

	float speed;
  float	mouseSpeed;

  glm::vec3 cursor;
  glm::vec3 position;

  Gameobject* _parent;

  glm::vec3 getParentPos(Gameobject* gameobject);

  glm::vec3 _localPosition;

  float _deltaTime;

};

#endif
