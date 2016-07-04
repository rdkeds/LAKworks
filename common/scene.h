#ifndef SCENE_H
#define SCENE_H

// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <string>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>

#include <common/camera.h>
#include <common/gameobject.h>

class Scene{
  public:
    Scene();
    virtual ~Scene();

    virtual void Update(GLFWwindow* window);

    std::vector <Gameobject*> ObjectsInScene() { return _objectsInScene; };

    std::vector <Gameobject*> _objectsInScene;

    Camera* cam() {return &_cam; };

    Camera _cam;

};

#endif
