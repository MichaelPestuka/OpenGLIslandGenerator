#include "window.hpp"

GLFWwindow* newWindow(int width, int height)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(width, height, "test", NULL, NULL);
    if(window == NULL)
    {
        glfwTerminate();
        std::cout << "Window creation error" << std::endl;
        return NULL;
    }

    glfwMakeContextCurrent(window);
    return window;
}