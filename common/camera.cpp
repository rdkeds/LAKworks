#include "common/camera.h"
#include <iostream>
#include <string>

Camera::Camera(){

	_parent = NULL;

	cursor = glm::vec3( 0, 0, 0 );

	position = glm::vec3( 0, 0, 0 );
	initialFoV = 45.0f;

	speed = 3.0f; // 3 units / second
	mouseSpeed = 0.002f;

}

Camera::~Camera(){

}


void Camera::computeMatricesFromInputs(GLFWwindow* window)
{
	// glfwGetTime is called only once, the first time this function is called
	static double lastTime = glfwGetTime();

	// Compute time difference between current and last frame
	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);

	// Get mouse position
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	if(ypos > 1150){
		ypos = 1150;
	} else if (ypos < -450){
		ypos = -450;
	}

	glfwSetCursorPos(window, xpos, ypos);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	horizontalAngle = 3.14f + mouseSpeed * float( 1280/2 - xpos );
	verticalAngle   = mouseSpeed * float( 720/2 - ypos );

	if(verticalAngle < -0.7f){
		//verticalAngle = -0.7f;
	}

	// Direction : Spherical coordinates to Cartesian coordinates conversion
	glm::vec3 direction(
		cos(verticalAngle) * sin(horizontalAngle),
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);

	// Right vector
	glm::vec3 right = glm::vec3(
		sin(horizontalAngle - 3.14f/2.0f),
		0,
		cos(horizontalAngle - 3.14f/2.0f)
	);

	// Up vector
	glm::vec3 up = glm::cross( right, direction );

	// Move forward
	if (glfwGetKey( window, GLFW_KEY_UP ) == GLFW_PRESS){
		position += direction * deltaTime * speed;
	}
	// Move backward
	if (glfwGetKey( window, GLFW_KEY_DOWN ) == GLFW_PRESS){
		position -= direction * deltaTime * speed;
	}
	// Strafe right
	if (glfwGetKey( window, GLFW_KEY_RIGHT ) == GLFW_PRESS){
		position += right * deltaTime * speed;
	}
	// Strafe left
	if (glfwGetKey( window, GLFW_KEY_LEFT ) == GLFW_PRESS){
		position -= right * deltaTime * speed;
	}

	float FoV = initialFoV;// - 5 * glfwGetMouseWheel(); // Now GLFW 3 requires setting up a callback for this. It's a bit too complicated for this beginner's tutorial, so it's disabled instead.

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	ProjectionMatrix = glm::perspective(FoV, 4.0f / 3.0f, 0.1f, 100.0f);

	ViewMatrix       = glm::lookAt(
		position,           // Camera is here
		position+direction, // and looks here : at the same position, plus "direction"
		up                  // Head is up (set to 0,-1,0 to look upside-down)
	);

	// For the next frame, the "last time" will be "now"
	lastTime = currentTime;
}

glm::vec3 Camera::getParentPos(Gameobject* gameobject){

		if(gameobject->Parent() != NULL){

			return gameobject->position() + getParentPos(gameobject->Parent());

		} else {

			return gameobject->position();

		}

}

void Camera::computeMatricesFromInputs(GLFWwindow* window, glm::vec3 newPos) {
	// glfwGetTime is called only once, the first time this function is called
	static double lastTime = glfwGetTime();

	// Compute time difference between current and last frame
	double currentTime = glfwGetTime();
	_deltaTime = float(currentTime - lastTime);

	// Get mouse position
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	if(ypos > 1150){
		ypos = 1150;
	} else if (ypos < -450){
		ypos = -450;
	}

	glfwSetCursorPos(window, xpos, ypos);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	horizontalAngle = 3.14f + mouseSpeed * float( 1280/2 - xpos );
	verticalAngle   = mouseSpeed * float( 720/2 - ypos );

	if(verticalAngle < -0.7f){
		//verticalAngle = -0.7f;
	}

	// Direction : Spherical coordinates to Cartesian coordinates conversion
	glm::vec3 direction(
		cos(verticalAngle) * sin(horizontalAngle),
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);

	// Right vector
	glm::vec3 right = glm::vec3(
		sin(horizontalAngle - 3.14f/2.0f),
		0,
		cos(horizontalAngle - 3.14f/2.0f)
	);

	// Up vector
	glm::vec3 up = glm::cross( right, direction );

	if(this->parent()->Parent() != NULL){

		glm::vec3 parentPos = getParentPos(this->parent());

		position = newPos + parentPos + _localPosition;

	} else {

		position = newPos + _localPosition;

	}



	float FoV = initialFoV;// - 5 * glfwGetMouseWheel(); // Now GLFW 3 requires setting up a callback for this. It's a bit too complicated for this beginner's tutorial, so it's disabled instead.

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	ProjectionMatrix = glm::perspective(FoV, 4.0f / 3.0f, 0.1f, 100.0f);

	ViewMatrix       = glm::lookAt(
		position,           // Camera is here
		position+direction, // and looks here : at the same position, plus "direction"
		up                  // Head is up (set to 0,-1,0 to look upside-down)
	);

	// For the next frame, the "last time" will be "now"
	lastTime = currentTime;
}
