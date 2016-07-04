#include "gameobject.h"
#include <iostream>
#include <string>

Gameobject::Gameobject(std::string object_file,std::string texture_file){

  _parent = NULL;

  this->position(glm::vec3(0.0f, 0.0f, 0.0f));
	this->scale(glm::vec3(1.0f, 1.0f, 1.0f));
	this->rotX(0.0f);
	this->rotY(0.0f);
	this->rotZ(0.0f);

  this->localPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	this->localScale(glm::vec3(0.0f, 0.0f, 0.0f));
	this->localRotX(0.0f);
	this->localRotY(0.0f);
	this->localRotZ(0.0f);

  Texture textureClass;

  // Load the texture (see: texture.h/cpp)
  _texture = textureClass.loadBMP_custom(texture_file.c_str());

  // Read our .obj file
  std::vector< glm::vec3 > vertices;
  std::vector< glm::vec2 > uvs;
  std::vector< glm::vec3 > normals; // Won't be used at the moment.
  bool res = loadOBJ(object_file.c_str(), vertices, uvs, normals);

  _tricount = vertices.size();

  _vertexbuffer;
  glGenBuffers(1, &_vertexbuffer);
  glBindBuffer(GL_ARRAY_BUFFER, _vertexbuffer);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

  _uvbuffer;
  glGenBuffers(1, &_uvbuffer);
  glBindBuffer(GL_ARRAY_BUFFER, _uvbuffer);
  glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);

  _normalbuffer;
  glGenBuffers(1, &_normalbuffer);
  glBindBuffer(GL_ARRAY_BUFFER, _normalbuffer);
  glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);

}

void Gameobject::setParent(Gameobject* newParent){

  if(_parent != NULL){

    _parent->removeChild(this);

  }

  _parent = newParent;

  this->localPosition(this->position() - _parent->position());
	this->localScale((this->scale() - glm::vec3(1.0f, 1.0f, 1.0f)));
	this->localRotX(this->rotX());
  this->localRotY(this->rotY());
  this->localRotZ(this->rotZ());

}

void Gameobject::addChild(Gameobject* newChild){

  newChild->setParent(this);

  _children.push_back(newChild);

}

void Gameobject::unChild(){

  if(_parent != NULL){

    this->position(_parent->position() + this->localPosition());
  	this->scale(_parent->scale() + this->localScale());
  	this->rotX(_parent->rotX() + this->localRotX());
  	this->rotY(_parent->rotY() + this->localRotY());
  	this->rotZ(_parent->rotZ() + this->localRotZ());

    _parent->removeChild(this);

  }

  _parent = NULL;

}

void Gameobject::removeChild(Gameobject* oldChild){

  _children.erase(std::remove(_children.begin(), _children.end(), oldChild), _children.end());

}

void Gameobject::addCollider(int type){

  if(type == 1){

    Collider* newCol = new Collider(1);
    _colliders.push_back(newCol);

  } else if (type == 2){

    Collider* newCol = new Collider(1,1,1);
    _colliders.push_back(newCol);

  } else {

    std::cout << "Error: The hell you doing with my collsions man?" << std::endl;

  }

}

void Gameobject::checkCollisions(std::vector <Gameobject*> otherObjectsInScene){

  for(int i = 0; i < otherObjectsInScene.size(); i++){

    if(otherObjectsInScene[i] != this){

      if(otherObjectsInScene[i]->colliders().size() > 0){

         for(int k = 0; k < otherObjectsInScene[i]->colliders().size(); k++){

            if(otherObjectsInScene[i]->colliders()[k]->colType() == 1){

              for(int l = 0; l < this->colliders().size(); l++){

                if(this->colliders()[l]->colType() == 1){

                  glm::vec3 diff = this->position() - otherObjectsInScene[i]->position();
                  float distance = sqrtf(dot(diff, diff));

                  if(distance < (this->colliders()[l]->rad() + otherObjectsInScene[i]->colliders()[k]->rad())){

                    this->onCollision();
                    break;

                  }

                } else if(this->colliders()[l]->colType() == 2){

                  if(checkSquareCol(this, otherObjectsInScene[i], l, k) == true){

                    this->onCollision();
                    break;

                  }

                }

              }

            } else if(otherObjectsInScene[i]->colliders()[k]->colType() == 2){

              for(int l = 0; l < this->colliders().size(); l++){

                if(this->colliders()[l]->colType() == 1){

                  if(checkSquareCol(otherObjectsInScene[i], this, k, l) == true){

                    this->onCollision();

                  }

                } else if(this->colliders()[l]->colType() == 2){

                  float diffX = 0;
                  float diffY = 0;
                  float diffZ = 0;

                  if(this->posX() >= otherObjectsInScene[i]->posX()){

                    diffX = this->posX() - otherObjectsInScene[i]->posX();

                  } else {

                    diffX = otherObjectsInScene[i]->posX() - this->posX();

                  }

                  if(this->posY() >= otherObjectsInScene[i]->posY()){

                    diffY = this->posY() - otherObjectsInScene[i]->posY();

                  } else {

                    diffY = otherObjectsInScene[i]->posY() - this->posY();

                  }

                  if(this->posZ() >= otherObjectsInScene[i]->posZ()){

                    diffZ = this->posZ() - otherObjectsInScene[i]->posZ();

                  } else {

                    diffZ = otherObjectsInScene[i]->posZ() - this->posZ();

                  }

                  bool check1 = false;
                  bool check2 = false;
                  bool check3 = false;

                  if(diffX < (this->colliders()[l]->distX() + otherObjectsInScene[i]->colliders()[k]->distX())){

                    check1 = true;

                  }

                  if(diffY < (this->colliders()[l]->distY() + otherObjectsInScene[i]->colliders()[k]->distY())){

                    check2 = true;

                  }

                  if(diffZ < (this->colliders()[l]->distZ() + otherObjectsInScene[i]->colliders()[k]->distZ())){

                    check3 = true;

                  }

                  if(check1 == true && check2 == true && check3 == true){

                    this->onCollision();

                  }

                }

              }

            }

         }

      }

    }

  }

}

bool Gameobject::checkSquareCol(Gameobject* squareCol, Gameobject* sphereCol, int l, int k){

  float diffX = 0;
  float diffY = 0;
  float diffZ = 0;

  if(squareCol->posX() >= sphereCol->posX()){

    diffX = squareCol->posX() - sphereCol->posX();

  } else {

    diffX = sphereCol->posX() - squareCol->posX();

  }

  if(squareCol->posY() >= sphereCol->posY()){

    diffY = squareCol->posY() - sphereCol->posY();

  } else {

    diffY = sphereCol->posY() - squareCol->posY();

  }

  if(squareCol->posZ() >= sphereCol->posZ()){

    diffZ = squareCol->posZ() - sphereCol->posZ();

  } else {

    diffZ = sphereCol->posZ() - squareCol->posZ();

  }

  bool check1 = false;
  bool check2 = false;
  bool check3 = false;
  bool check4 = false;
  bool check5 = false;
  bool check6 = false;
  bool check7 = false;

  if(diffX < (squareCol->colliders()[l]->distX() + sphereCol->colliders()[k]->rad())){

    check1 = true;

  }

  if(diffY < (squareCol->colliders()[l]->distY() + sphereCol->colliders()[k]->rad())){

    check2 = true;

  }

  if(diffZ < (squareCol->colliders()[l]->distZ() + sphereCol->colliders()[k]->rad())){

    check3 = true;

  }

  float distanceXY = sqrtf(pow(diffX, 2) + pow(diffY, 2));
  float distanceZY = sqrtf(pow(diffZ, 2) + pow(diffY, 2));
  float distanceXZ = sqrtf(pow(diffX, 2) + pow(diffZ, 2));

  float rootOfXY = sqrtf(pow(squareCol->colliders()[l]->distX(), 2) + pow(squareCol->colliders()[l]->distY(), 2));
  float rootOfZY = sqrtf(pow(squareCol->colliders()[l]->distZ(), 2) + pow(squareCol->colliders()[l]->distY(), 2));
  float rootOfXZ = sqrtf(pow(squareCol->colliders()[l]->distZ(), 2) + pow(squareCol->colliders()[l]->distX(), 2));

  if(rootOfXY + sphereCol->colliders()[k]->rad() > distanceXY){

    check4 = true;

  }

  if(rootOfZY + sphereCol->colliders()[k]->rad() > distanceZY){

    check5 = true;

  }

  if(rootOfXZ + sphereCol->colliders()[k]->rad() > distanceXZ){

    check6 = true;

  }

  if((sqrtf(pow(rootOfXZ, 2) + pow(squareCol->colliders()[l]->distY(), 2)) + sphereCol->colliders()[k]->rad()) > sqrtf(pow(distanceXZ, 2) + pow(diffY, 2))){

    check7 = true;

  }

  if(check1 == true && check2 == true && check3 == true && check4 == true && check5 == true && check6 == true && check7 == true){

    return true;

  } else {

    return false;

  }

}

void Gameobject::onCollision(){

  std::cout << this << std::endl;
  std::cout << "Collision detected" << std::endl;

}

Gameobject::~Gameobject(){
  glDeleteBuffers(1, &_vertexbuffer);
	glDeleteBuffers(1, &_uvbuffer);
  glDeleteBuffers(1, &_normalbuffer);
}
