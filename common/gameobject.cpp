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

Gameobject::~Gameobject(){
  glDeleteBuffers(1, &_vertexbuffer);
	glDeleteBuffers(1, &_uvbuffer);
  glDeleteBuffers(1, &_normalbuffer);
}
