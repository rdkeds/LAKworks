// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <string>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>

#include <common/renderer.h>

#include "scene1.h"
#include "scene2.h"

int main( void )
{
	Renderer renderer;

	int currentScene = 0;

	std::vector<Scene*> allScenes;

	Scene* scene1 = new Scene1();
	Scene* scene2 = new Scene2();

	allScenes.push_back(scene1);
	allScenes.push_back(scene2);

	bool clicked = false;

	do {
		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if(glfwGetKey(renderer.window(), GLFW_KEY_1)){

			if(clicked == false){

				if(currentScene == 0){

					currentScene = 1;

				} else {

					currentScene = 0;

				}

				clicked = true;

			}

		} else {

			clicked = false;

		}

		renderer.renderScene(allScenes[currentScene]);

		// Swap buffers
		glfwSwapBuffers(renderer.window());
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(renderer.window(), GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(renderer.window()) == 0 );

	scene1->~Scene();
	scene2->~Scene();

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}
