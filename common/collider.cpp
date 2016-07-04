#include "collider.h"
#include <iostream>
#include <string>

Collider::Collider(float newRad){

  std::cout << "Sphere Collider Made" << std::endl;

  colType(1);

  _rad = newRad;

}

Collider::Collider(float newDX, float newDY, float newDZ){

  std::cout << "Cube Collider Made" << std::endl;

  colType(2);

  _distX = newDX;
  _distY = newDY;
  _distZ = newDZ;

}

Collider::~Collider(){

}
