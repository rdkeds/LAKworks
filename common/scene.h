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

#include <common/gameobject.h>
#include <common/light.h>

class Scene{
  public:
    Scene();
    virtual ~Scene();

    virtual void Update();

    std::vector <Gameobject*> ObjectsInScene() { return _objectsInScene; };
    std::vector <Light*> LightsInScene() { return _lightsInScene; };

    std::vector <Gameobject*> _objectsInScene;
    std::vector <Light*> _lightsInScene;

};

#endif
