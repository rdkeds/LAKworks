#include "scene1.h"

Scene1::Scene1(){

  gameobject = new Gameobject("assets/boompje.obj", "assets/boompje.bmp");

  _objectsInScene.push_back(gameobject);

  gameobject2 = new Gameobject("assets/boompje.obj", "assets/boompje.bmp");

  _objectsInScene.push_back(gameobject2);

  gameobject->position(glm::vec3(-1.5f, 0.0f, 0.0f));
  gameobject2->position(glm::vec3(1.5f, 0.0f, 0.0f));

  gameobject->addChild(gameobject2);

}

void Scene1::Update(){

  //gameobject->position(gameobject->position() + glm::vec3(-0.01f, 0.0f, 0.0f));

  //gameobject->rotX(gameobject->rotX() + 0.01f);
  gameobject->rotY(gameobject->rotY() + 0.01f);

}

Scene1::~Scene1(){

  delete gameobject;

}
