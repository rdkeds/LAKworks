#include "scene2.h"

Scene2::Scene2(){

  gameobject = new Gameobject("assets/test.obj", "assets/256.bmp");
	gameobject2 = new Gameobject("assets/test.obj", "assets/1024.bmp");

  gameobject->position(glm::vec3(-1.5f, 0.0f, 0.0f));
	gameobject->scale(glm::vec3(1.0f, 1.0f, 1.0f));
	gameobject->rotX(0.0f);
	gameobject->rotY(0.0f);
	gameobject->rotZ(0.0f);

	gameobject2->position(glm::vec3(1.5f, 0.0f, 0.0f));
	gameobject2->scale(glm::vec3(1.0f, 1.0f, 1.0f));
	gameobject2->rotX(0.0f);
	gameobject2->rotY(0.0f);
	gameobject2->rotZ(0.0f);

  _objectsInScene.push_back(gameobject);
  _objectsInScene.push_back(gameobject2);

}

void Scene2::Update(){

  gameobject->rotY(gameobject->rotY() + 0.01f);
  gameobject2->rotY(gameobject2->rotY() - 0.01f);

}

Scene2::~Scene2(){

  delete gameobject;
  delete gameobject2;

}
