#ifndef COLLIDER_H
#define COLLIDER_H

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

class Collider{
  public:
    Collider(float newRad);
    Collider(float newDX, float newDY, float newDZ);
    virtual ~Collider();

    float rad() { return _rad; };
    void rad(float newRad) { _rad = newRad; };

    float distX() { return _distX; };
    void distX(float newDX) { _distX = newDX; };
    float distY() { return _distY; };
    void distY(float newDY) { _distY = newDY; };
    float distZ() { return _distZ; };
    void distZ(float newDZ) { _distZ = newDZ; };

    int colType() { return _colType; };
    void colType(int newCT) { _colType = newCT; };


	private:

    float _rad; //radius in case of Sphere collider (All sides)

    float _distX; //X length of collider in case of Cube collider
    float _distY; //Y length of collider in case of Cube collider
    float _distZ; //Z length of collider in case of Cube collider

    int _colType; //1 = Sphere, 2 = Cube

    std::string object_file;
    std::string texture_file;

};

#endif
