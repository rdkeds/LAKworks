#include "scene1.h"

Scene1::Scene1(){

  gameobject = new Gameobject("assets/boompje.obj", "assets/boompje.bmp");

  gameobject->position(glm::vec3(0.0f, 0.0f, 0.0f));
	gameobject->scale(glm::vec3(1.0f, 1.0f, 1.0f));
	gameobject->rotX(0.0f);
	gameobject->rotY(0.0f);
	gameobject->rotZ(0.0f);

  _objectsInScene.push_back(gameobject);

  light = new Light();

  _lightsInScene.push_back(light);

}

void Scene1::Update(){

  gameobject->rotX(gameobject->rotX() + 0.01f);
  gameobject->rotY(gameobject->rotY() + 0.01f);

}

Scene1::~Scene1(){

  delete gameobject;
  delete light;

}
