#include "scene1.h"

Scene1::Scene1(){

  gameobject = new Gameobject("assets/collidersphere.obj", "assets/green.bmp");
  _objectsInScene.push_back(gameobject);

  gameobject->addCollider(1);
  gameobject->rotY(0.78);

  gameobject2 = new Gameobject("assets/collidercube.obj", "assets/green.bmp");
  _objectsInScene.push_back(gameobject2);

  gameobject2->addCollider(2);

  gameobject->position(glm::vec3(1.60f, 1.60f, 1.60f));
  gameobject2->position(glm::vec3(0.0f, 0.0f, 0.0f));

  //_cam.parent(gameobject);

}

void Scene1::Update(GLFWwindow* window){

  //gameobject->position(gameobject->position() + glm::vec3(-0.01f, 0.0f, 0.0f));


}

Scene1::~Scene1(){

  delete gameobject;
  delete gameobject2;

}
