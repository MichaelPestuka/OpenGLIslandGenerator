#ifndef TEXTURE_H
#define TEXTURE_h

#include "include/stb_image.h"

#include "include/glad/glad.h"
#include <GLFW/glfw3.h>

#include <iostream>

int TextureFromImageFile(const char* filename);

int AlphaTextureFromCharArray(uint8_t* data, int width, int height);

#endif