#include <common/renderer.h>

Renderer::Renderer(){
  Camera cam;

  window_width = 1280;
  window_height = 720;

  fragment_shader	= "shaders/sprite.frag";
  vertex_shader	= "shaders/sprite.vert";

  this->init();
}

Renderer::~Renderer(){
  // Cleanup VBO and shader
  glDeleteProgram(programID);
  glDeleteTextures(1, &textureID);
}

int Renderer::init(){
  // Initialise GLFW
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

	// Open a window and create its OpenGL context
	_window = glfwCreateWindow( window_width, window_height, "Demo", NULL, NULL);
	if( _window == NULL ){
		fprintf( stderr, "Failed to open GLFW window.\n" );
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(_window);

	// Initialize GLEW
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(_window, GLFW_STICKY_KEYS, GL_TRUE);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);

	// Create and compile our GLSL program from the shaders
	// see: shader.h/cpp
	programID = loadShaders(vertex_shader.c_str(), fragment_shader.c_str());

	// Get a handle for our buffers
	vertexPosition_modelspaceID = glGetAttribLocation(programID, "vertexPosition_modelspace");
	vertexUVID = glGetAttribLocation(programID, "vertexUV");
  vertexNormal_modelspaceID = glGetAttribLocation(programID, "vertexNormal_modelspace");

	// Get a handle for our "MVP" uniform
	matrixID = glGetUniformLocation(programID, "MVP");
  ViewMatrixID = glGetUniformLocation(programID, "V");
	ModelMatrixID = glGetUniformLocation(programID, "M");

	// Get a handle for our "myTextureSampler" uniform
	textureID  = glGetUniformLocation(programID, "myTextureSampler");

  // Get a handle for our "LightPosition" uniform
	//LightID = glGetUniformLocation(programID, "LightPosition_worldspace");

  //ProjectionMatrix = glm::ortho(0.0f, (float)window_width, (float)window_height, 0.0f, 0.1f, 100.0f);
  ProjectionMatrix = glm::perspective(100.0f, 4.0f / 3.0f, 0.1f, 1000.0f);

  return 0;
}

void Renderer::renderSprite(Sprite* sprite){
  // Compute the ViewMatrix from keyboard and mouse input (see: camera.h/cpp)
  cam.computeMatricesFromInputs(_window);

  glm::vec3 cursor = cam.getCursor();
  //printf("(%f,%f)\n",cursor.x, cursor.y);

  glm::mat4 ViewMatrix = cam.getViewMatrix(); // get from Camera (Camera position and direction)
  glm::mat4 ModelMatrix = glm::mat4(1.0f);

  // Use our shader
  glUseProgram(programID);

  // Build the Model matrix
  glm::mat4 translationMatrix	= glm::translate(glm::mat4(1.0f), sprite->position());
  glm::mat4 rotationMatrix	= glm::eulerAngleYXZ(sprite->rotY(), sprite->rotX(), sprite->rotZ());
  glm::mat4 scalingMatrix		= glm::scale(glm::mat4(1.0f), sprite->scale());

  ModelMatrix = translationMatrix * rotationMatrix * scalingMatrix;

  glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

  // Send our transformation to the currently bound shader,
  // in the "MVP" uniform
  glUniformMatrix4fv(matrixID, 1, GL_FALSE, &MVP[0][0]);

  // Bind our texture in Texture Unit 0
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, sprite->texture());
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  // Set our "myTextureSampler" sampler to user Texture Unit 0
  glUniform1i(textureID, 0);

  // 1st attribute buffer : vertices
  glEnableVertexAttribArray(vertexPosition_modelspaceID);
  glBindBuffer(GL_ARRAY_BUFFER, sprite->vertexbuffer());
  glVertexAttribPointer(
    vertexPosition_modelspaceID,  // The attribute we want to configure
    3,                            // size : x+y+z => 3
    GL_FLOAT,                     // type
    GL_FALSE,                     // normalized?
    0,                            // stride
    (void*)0                      // array buffer offset
  );

  // 2nd attribute buffer : UVs
  glEnableVertexAttribArray(vertexUVID);
  glBindBuffer(GL_ARRAY_BUFFER, sprite->uvbuffer());
  glVertexAttribPointer(
    vertexUVID,                   // The attribute we want to configure
    2,                            // size : U+V => 2
    GL_FLOAT,                     // type
    GL_FALSE,                     // normalized?
    0,                            // stride
    (void*)0                      // array buffer offset
  );

  // Draw the triangles !
  glDrawArrays(GL_TRIANGLES, 0, 2*3); // 2*3 indices starting at 0 -> 2 triangles

  glDisableVertexAttribArray(vertexPosition_modelspaceID);
  glDisableVertexAttribArray(vertexUVID);
}

void Renderer::renderObject(Gameobject* gameobject){
  // Compute the ViewMatrix from keyboard and mouse input (see: camera.h/cpp)
  cam.computeMatricesFromInputs(_window);

  glm::vec3 cursor = cam.getCursor();
  //printf("(%f,%f)\n",cursor.x, cursor.y);

  glm::mat4 ViewMatrix = cam.getViewMatrix(); // get from Camera (Camera position and direction)
  glm::mat4 ModelMatrix = glm::mat4(1.0f);

  // Use our shader
  glUseProgram(programID);

  // Build the Model matrix
  glm::mat4 translationMatrix	= glm::translate(glm::mat4(1.0f), gameobject->position());
  glm::mat4 rotationMatrix	= glm::eulerAngleYXZ(gameobject->rotY(), gameobject->rotX(), gameobject->rotZ());
  glm::mat4 scalingMatrix		= glm::scale(glm::mat4(1.0f), gameobject->scale());

  ModelMatrix = translationMatrix * rotationMatrix * scalingMatrix;

  glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

  // Send our transformation to the currently bound shader,
  // in the "MVP" uniform
  glUniformMatrix4fv(matrixID, 1, GL_FALSE, &MVP[0][0]);
  glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
  glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);

  /*glm::vec3 lightPos = glm::vec3(4,4,4);
  glUniform3f(LightID, lightPos.x, lightPos.y, lightPos.z);*/

  // Bind our texture in Texture Unit 0
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, gameobject->texture());
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  // Set our "myTextureSampler" sampler to user Texture Unit 0
  glUniform1i(textureID, 0);

  // 1st attribute buffer : vertices
  glEnableVertexAttribArray(vertexPosition_modelspaceID);
  glBindBuffer(GL_ARRAY_BUFFER, gameobject->vertexbuffer());
  glVertexAttribPointer(
    vertexPosition_modelspaceID,  // The attribute we want to configure
    3,                            // size : x+y+z => 3
    GL_FLOAT,                     // type
    GL_FALSE,                     // normalized?
    0,                            // stride
    (void*)0                      // array buffer offset
  );

  // 2nd attribute buffer : UVs
  glEnableVertexAttribArray(vertexUVID);
  glBindBuffer(GL_ARRAY_BUFFER, gameobject->uvbuffer());
  glVertexAttribPointer(
    vertexUVID,                   // The attribute we want to configure
    2,                            // size : U+V => 2
    GL_FLOAT,                     // type
    GL_FALSE,                     // normalized?
    0,                            // stride
    (void*)0                      // array buffer offset
  );

  // 3rd attribute buffer : normals
  glEnableVertexAttribArray(vertexNormal_modelspaceID);
  glBindBuffer(GL_ARRAY_BUFFER, gameobject->normalbuffer());
  glVertexAttribPointer(
    vertexNormal_modelspaceID,    // The attribute we want to configure
    3,                            // size
    GL_FLOAT,                     // type
    GL_FALSE,                     // normalized?
    0,                            // stride
    (void*)0                      // array buffer offset
  );

  // Draw the triangles !
  glDrawArrays(GL_TRIANGLES, 0, gameobject->tricount()*3); // 12*3 indices starting at 0 -> 12 triangles

  glDisableVertexAttribArray(vertexPosition_modelspaceID);
  glDisableVertexAttribArray(vertexUVID);
  glDisableVertexAttribArray(vertexNormal_modelspaceID);
}

void Renderer::renderScene(Scene* scene){

  scene->Update();

  std::vector<Gameobject*> objectsInRenderedScene;
  objectsInRenderedScene = scene->ObjectsInScene();

  for(int i = 0; i < objectsInRenderedScene.size(); i++){

    renderObject(objectsInRenderedScene[i]);

  }

}
