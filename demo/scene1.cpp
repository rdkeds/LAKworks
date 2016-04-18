#include "scene1.h"

Scene1::Scene1(){

  gameobject = new Gameobject("assets/boompje.obj", "assets/boompje.bmp");

  _objectsInScene.push_back(gameobject);

  gameobject2 = new Gameobject("assets/boompje.obj", "assets/boompje.bmp");

  _objectsInScene.push_back(gameobject2);

  gameobject3 = new Gameobject("assets/boompje.obj", "assets/boompje.bmp");

  _objectsInScene.push_back(gameobject3);

  gameobject->position(glm::vec3(0.0f, 0.0f, 0.0f));
  gameobject2->position(glm::vec3(2.0f, 0.0f, 0.0f));
  gameobject3->position(glm::vec3(-4.0f, 0.0f, 0.0f));

  gameobject->addChild(gameobject2);
  gameobject2->addChild(gameobject3);

}

void Scene1::Update(){

  //gameobject->position(gameobject->position() + glm::vec3(-0.01f, 0.0f, 0.0f));

  gameobject->rotY(gameobject->rotY() + 0.01f);
  gameobject2->rotY(gameobject2->rotY() + 0.01f);
  gameobject3->rotZ(gameobject3->rotZ() + 0.01f);

}

Scene1::~Scene1(){

  delete gameobject;
  delete gameobject2;
  delete gameobject3;

}
