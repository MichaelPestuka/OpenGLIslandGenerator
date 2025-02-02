#ifndef WINDOW_H
#define WINDOW_H

#include "include/glad/glad.h"
#include <GLFW/glfw3.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

GLFWwindow *newWindow(int width, int height);

#endif