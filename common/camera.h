#ifndef CAMERA_H
#define CAMERA_H

// Include GLFW
#include <glfw3.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
  public:
    Camera();
    virtual ~Camera();

    void computeMatricesFromInputs(GLFWwindow* window);
    glm::mat4 getViewMatrix() {return ViewMatrix; };
    glm::vec3 getCursor() {return cursor; };
private:

  glm::mat4 ViewMatrix;

  float speed;
  glm::vec3 cursor;
  glm::vec3 position;

};

#endif
