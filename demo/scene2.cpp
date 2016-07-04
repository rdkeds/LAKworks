#include "scene2.h"

Scene2::Scene2(){

  playerController = new Gameobject("assets/collidersphere.obj", "assets/green.bmp");
  _objectsInScene.push_back(playerController);

  playerController->addCollider(1);

  playerController->position(glm::vec3(0.0f, 0.0f, -3.0f));

  cockpitWalls = new Gameobject("assets/cockpitwalls.obj", "assets/walls.bmp");
	cockpitChair1 = new Gameobject("assets/cockpitchair.obj", "assets/CapChairTexture.bmp");
  cockpitChair2 = new Gameobject("assets/cockpitchair.obj", "assets/CapChairTexture.bmp");
  cockpitChair3 = new Gameobject("assets/cockpitchair.obj", "assets/CapChairTexture.bmp");
  cockpitTerminal = new Gameobject("assets/cockpitterminal.obj", "assets/CockpitTerminal.bmp");
  cockpitScreen1 = new Gameobject("assets/cockpitscreen.obj", "assets/screen.bmp");
  cockpitScreen2 = new Gameobject("assets/cockpitscreen.obj", "assets/screen.bmp");
  cockpitScreen3 = new Gameobject("assets/cockpitscreen.obj", "assets/screen.bmp");
  cockpitSteer1 = new Gameobject("assets/cockpitsteer.obj", "assets/steer.bmp");
  cockpitSteer2 = new Gameobject("assets/cockpitsteer.obj", "assets/steer.bmp");
  cockpitMapBase = new Gameobject("assets/cockpitmapbase.obj", "assets/mapbase.bmp");
  cockpitHoloCone = new Gameobject("assets/cockpitholo.obj", "assets/blue.bmp");
  cockpitHoloSphere1 = new Gameobject("assets/cockpitholosphere.obj", "assets/blue.bmp");
  cockpitHoloSphere2 = new Gameobject("assets/cockpitholosphere.obj", "assets/blue.bmp");
  cockpitHoloSphere3 = new Gameobject("assets/cockpitholosphere.obj", "assets/blue.bmp");
  cockpitHoloSphere4 = new Gameobject("assets/cockpitholosphere.obj", "assets/blue.bmp");
  cockpitHoloSphere5 = new Gameobject("assets/cockpitholosphere.obj", "assets/blue.bmp");
  cockpitFloor = new Gameobject("assets/cockpitfloor.obj", "assets/floor2.bmp");

  cockpitWalls->position(glm::vec3(0.0f, 0.0f, 0.0f));


  cockpitWalls->addChild(cockpitChair1);
  cockpitWalls->addChild(cockpitChair2);
  cockpitWalls->addChild(cockpitChair3);
  cockpitWalls->addChild(cockpitTerminal);
  cockpitWalls->addChild(cockpitScreen1);
  cockpitWalls->addChild(cockpitScreen2);
  cockpitWalls->addChild(cockpitScreen3);
  cockpitWalls->addChild(cockpitSteer1);
  cockpitWalls->addChild(cockpitSteer2);
  cockpitWalls->addChild(cockpitMapBase);
  cockpitMapBase->addChild(cockpitHoloCone);
  cockpitHoloCone->addChild(cockpitHoloSphere1);
  cockpitHoloSphere1->addChild(cockpitHoloSphere2);
  cockpitHoloCone->addChild(cockpitHoloSphere3);
  cockpitHoloCone->addChild(cockpitHoloSphere4);
  cockpitHoloCone->addChild(cockpitHoloSphere5);
  cockpitWalls->addChild(cockpitFloor);


	cockpitChair1->position(glm::vec3(0.953f, 0.312f, -1.276f));
  cockpitChair2->position(glm::vec3(-0.953f, 0.312f, -1.276f));
  cockpitChair3->position(glm::vec3(1.346f, 0.312f, -3.448f));
  cockpitChair3->rotY(2.4f);
  cockpitTerminal->position(glm::vec3(0, 0, -1.518));
  cockpitScreen1->position(glm::vec3(-1.925, 1.103, -3.971));
  cockpitScreen1->rotX(1.57);
  cockpitScreen1->rotZ(-1.58);
  cockpitScreen2->position(glm::vec3(-1.925, 1.103, -3.433));
  cockpitScreen2->rotX(1.57);
  cockpitScreen2->rotZ(-1.58);
  cockpitScreen3->position(glm::vec3(1.774, 1.219, -3.932));
  cockpitScreen3->scale(glm::vec3(1.5, 1.5, 1.5));
  cockpitScreen3->rotX(1.57);
  cockpitScreen3->rotZ(0.785);
  cockpitSteer1->position(glm::vec3(-0.976, 0.508, -0.549));
  cockpitSteer1->rotX(0.5);
  cockpitSteer2->position(glm::vec3(0.976, 0.508, -0.549));
  cockpitSteer2->rotX(0.5);
  cockpitMapBase->position(glm::vec3(0, 0.395, -1.803));
  cockpitHoloCone->position(glm::vec3(0, 0.1, 0));
  cockpitHoloSphere1->position(glm::vec3(0.15, 0.5, 0.1));
  cockpitHoloSphere1->scale(glm::vec3(1.5, 1.5, 1.5));
  cockpitHoloSphere2->position(glm::vec3(-0.05, 0, 0.05));
  cockpitHoloSphere2->scale(glm::vec3(0.3, 0.3, 0.3));
  cockpitHoloSphere3->position(glm::vec3(-0.1, 0.4, 0.05));
  cockpitHoloSphere4->position(glm::vec3(0.05, 0.25, -0.03));
  cockpitHoloSphere5->position(glm::vec3(-0.1, 0.2, -0.01));
  cockpitHoloSphere5->scale(glm::vec3(0.6, 0.6, 0.6));
  cockpitFloor->position(glm::vec3(0, 0, -2.293));

  _objectsInScene.push_back(cockpitWalls);
  _objectsInScene.push_back(cockpitChair1);
  _objectsInScene.push_back(cockpitChair2);
  _objectsInScene.push_back(cockpitChair3);
  _objectsInScene.push_back(cockpitTerminal);
  _objectsInScene.push_back(cockpitScreen1);
  _objectsInScene.push_back(cockpitScreen2);
  _objectsInScene.push_back(cockpitScreen3);
  _objectsInScene.push_back(cockpitSteer1);
  _objectsInScene.push_back(cockpitSteer2);
  _objectsInScene.push_back(cockpitMapBase);
  _objectsInScene.push_back(cockpitHoloCone);
  _objectsInScene.push_back(cockpitHoloSphere1);
  _objectsInScene.push_back(cockpitHoloSphere2);
  _objectsInScene.push_back(cockpitHoloSphere3);
  _objectsInScene.push_back(cockpitHoloSphere4);
  _objectsInScene.push_back(cockpitHoloSphere5);
  _objectsInScene.push_back(cockpitFloor);

  _cam.localPosition(glm::vec3(0.0f, 1.5f, 0.0f));
  _cam.parent(playerController);

}

void Scene2::Update(GLFWwindow* window){

  float dt = this->cam()->deltaTime();

  cockpitHoloCone->rotY(cockpitHoloSphere1->rotY() + (300.0f * dt));

  cockpitHoloSphere1->rotY(cockpitHoloSphere1->rotY() - (200.0f * dt));
  cockpitHoloSphere2->rotY(cockpitHoloSphere2->rotY() - (200.0f * dt));
  cockpitHoloSphere3->rotY(cockpitHoloSphere3->rotY() - (200.0f * dt));
  cockpitHoloSphere4->rotY(cockpitHoloSphere4->rotY() - (200.0f * dt));
  cockpitHoloSphere5->rotY(cockpitHoloSphere5->rotY() - (200.0f * dt));

  // Move forward
	if (glfwGetKey( window, GLFW_KEY_UP ) == GLFW_PRESS){
		playerController->position(glm::vec3(playerController->posX(), playerController->posY(), playerController->posZ() + (50.0f * dt)));
	}
	// Move backward
	if (glfwGetKey( window, GLFW_KEY_DOWN ) == GLFW_PRESS){
    playerController->position(glm::vec3(playerController->posX(), playerController->posY(), playerController->posZ() - (50.0f * dt)));
	}
	// Strafe right
	if (glfwGetKey( window, GLFW_KEY_RIGHT ) == GLFW_PRESS){
    playerController->position(glm::vec3(playerController->posX() - (50.0f * dt), playerController->posY(), playerController->posZ()));
	}
	// Strafe left
	if (glfwGetKey( window, GLFW_KEY_LEFT ) == GLFW_PRESS){
    playerController->position(glm::vec3(playerController->posX() + (50.0f * dt), playerController->posY(), playerController->posZ()));
	}

}

Scene2::~Scene2(){

  delete cockpitWalls;
  delete cockpitChair1;
  delete cockpitChair2;
  delete cockpitChair3;
  delete cockpitTerminal;
  delete cockpitScreen1;
  delete cockpitScreen2;
  delete cockpitScreen3;
  delete cockpitSteer1;
  delete cockpitSteer2;
  delete cockpitMapBase;
  delete cockpitHoloCone;
  delete cockpitHoloSphere1;
  delete cockpitHoloSphere2;
  delete cockpitHoloSphere3;
  delete cockpitHoloSphere4;
  delete cockpitHoloSphere5;
  delete cockpitFloor;

}
