#ifndef RENDERER_H
#define RENDERER_H

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

#include <common/shader.h>
#include <common/scene.h>
#include <common/sprite.h>
#include <common/gameobject.h>
#include <common/texture.h>
#include <common/camera.h>

class Renderer {
  public:
    Renderer();
		virtual ~Renderer();

    void renderSprite(Sprite* sprite);
    void renderObject(Gameobject* gameobject);
    void renderScene(Scene* scene);
		GLFWwindow* window() { return _window; };
  private:
    int init();

    Camera cam;

    GLFWwindow* _window;
		int window_width;
		int window_height;

    std::string fragment_shader;
		std::string vertex_shader;

    GLuint programID;
		GLuint vertexPosition_modelspaceID;
		GLuint vertexUVID;
    GLuint vertexNormal_modelspaceID;
		GLuint matrixID;
    GLuint ViewMatrixID;
    GLuint ModelMatrixID;
		GLuint textureID;
    GLuint LightID;

    glm::mat4 ProjectionMatrix;

    glm::mat4 GetParentMatrix(Gameobject* gameobject);
};

#endif
