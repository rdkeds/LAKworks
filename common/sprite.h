#ifndef SPRITE_H
#define SPRITE_H

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

#include <common/texture.h>

class Sprite{
  public:
    Sprite(std::string texture_file);
    virtual ~Sprite();

    GLuint texture() { return _texture; };
		GLuint vertexbuffer() { return _vertexbuffer; };
		GLuint uvbuffer() { return _uvbuffer; };

    glm::vec3 position() { return _position; };
    glm::vec3 position(glm::vec3 newPos) { _position = newPos; };

    glm::vec3 scale() { return _scale; };
    glm::vec3 scale(glm::vec3 newScl) { _scale = newScl; };

    float rotX() { return _rotX; };
    float rotX(float newX) { _rotX = newX; };
    float rotY() { return _rotY; };
    float rotY(float newY) { _rotY = newY; };
    float rotZ() { return _rotZ; };
    float rotZ(float newZ) { _rotZ = newZ; };

	private:
		GLuint _texture;
		GLuint _vertexbuffer;
		GLuint _uvbuffer;

    glm::vec3 _position;
    glm::vec3 _scale;
    float _rotX;
    float _rotY;
    float _rotZ;

};

#endif
