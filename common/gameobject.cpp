#include "gameobject.h"

Gameobject::Gameobject(std::string object_file,std::string texture_file){
  //testing some stuff
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

Gameobject::~Gameobject(){
  glDeleteBuffers(1, &_vertexbuffer);
	glDeleteBuffers(1, &_uvbuffer);
  glDeleteBuffers(1, &_normalbuffer);
}
