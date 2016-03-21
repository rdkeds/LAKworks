#ifndef TEXTURE_H
#define TEXTURE_H

// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <string>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>

class Texture{
  public:
    Texture();
    virtual ~Texture();
    // Load a .BMP file using our custom loader
    GLuint loadBMP_custom(const char * imagepath);

    //// Since GLFW 3, glfwLoadTexture2D() has been removed. You have to use another texture loading library,
    //// or do it yourself (just like loadBMP_custom and loadDDS)
    //// Load a .TGA file using GLFW's own loader
    //GLuint loadTGA_glfw(const char * imagepath);

    // Load a .DDS file using GLFW's own loader
    GLuint loadDDS(const char * imagepath);

    int textureWidth() { return _textureWidth; };
    int textureHeight() { return _textureHeight; };
  private:
    int _textureWidth;
    int _textureHeight;
};
#endif
