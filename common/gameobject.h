#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

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

#include <common/objloader.hpp>
#include <common/texture.h>

class Gameobject{
  public:
    Gameobject(std::string object_file, std::string texture_file);
    virtual ~Gameobject();

    GLuint texture() { return _texture; };
		GLuint vertexbuffer() { return _vertexbuffer; };
		GLuint uvbuffer() { return _uvbuffer; };
    GLuint normalbuffer() { return _normalbuffer; };

    float tricount() { return _tricount; };

    glm::vec3 position() { return _position; };
    void position(glm::vec3 newPos) { _position = newPos; };

    glm::vec3 scale() { return _scale; };
    void scale(glm::vec3 newScl) { _scale = newScl; };

    float rotX() { return _rotX; };
    void rotX(float newX) { _rotX = newX; };
    float rotY() { return _rotY; };
    void rotY(float newY) { _rotY = newY; };
    float rotZ() { return _rotZ; };
    void rotZ(float newZ) { _rotZ = newZ; };

    glm::vec3 localPosition() { return _localPosition; };
    void localPosition(glm::vec3 newPos) { _localPosition = newPos; };

    glm::vec3 localScale() { return _localScale; };
    void localScale(glm::vec3 newScl) { _localScale = newScl; };

    float localRotX() { return _localRotX; };
    void localRotX(float newX) { _localRotX = newX; };
    float localRotY() { return _localRotY; };
    void localRotY(float newY) { _localRotY = newY; };
    float localRotZ() { return _localRotZ; };
    void localRotZ(float newZ) { _localRotZ = newZ; };

    std::vector <Gameobject*> Children() { return _children; };
    Gameobject* Parent() {return _parent; };

    void setParent(Gameobject* newParent);
    void addChild(Gameobject* newChild);
    void unChild();
    void removeChild(Gameobject* oldChild);


	private:
		GLuint _texture;
		GLuint _vertexbuffer;
		GLuint _uvbuffer;
    GLuint _normalbuffer;

    float _tricount;

    glm::vec3 _position;
    glm::vec3 _scale;
    float _rotX;
    float _rotY;
    float _rotZ;

    glm::vec3 _localPosition;
    glm::vec3 _localScale;
    float _localRotX;
    float _localRotY;
    float _localRotZ;

    std::vector <Gameobject*> _children;
    Gameobject* _parent;

};

#endif
