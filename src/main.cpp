#include <cstdint>
#include <cstdlib>
#include <glm/ext/vector_float3.hpp>
#include <iostream>
#include <ostream>
#include <string>
#include <cmath>
#include <vector>

#include "include/glad/glad.h"
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "mesh.hpp"
#include "shader.hpp"
#include "window.hpp"
#include "camera.hpp"
#include "mesh_generator.hpp"
#include "texture.hpp"


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void mouseCallback(GLFWwindow *window, double xpos, double ypos);

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

glm::vec3 lightPos = glm::vec3(0.0f, 0.0f, 3.0f);

int windowHeight = 900;
int windowWidth = 1200;

float lastX = 0.0f;
float lastY = 0.0f;

float lastFrame = 0.0f;
float deltaTime = 0.0f;

float yaw = -90.0f;
float pitch = 0.0f;

Camera camera(cameraPos, cameraPos + cameraFront, cameraUp);

int main()
{
    GLFWwindow *window = newWindow(windowWidth, windowHeight);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouseCallback);

    lastX = windowWidth / 2.0;
    lastY = windowHeight / 2.0;
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    } 
    glViewport(0, 0, windowWidth, windowHeight); 

    Shader shader("shaders/vertex.glsl", "shaders/fragment.glsl");

    int div = 200;
    std::vector<float> planeVertices = PlaneVertices(div, 20.0f, false);
    std::vector<uint32_t> planeIndices = PlaneIndices(div);

    std::cout << "pretexture" << std::endl;
    unsigned int texture = TextureFromImageFile("grass.jpg");

    uint8_t proctex[div * div];
    for (int i = 0; i < div*div; i++) {
        // proctex[i] = rand() % 256;
        proctex[i] = (uint8_t)(planeVertices[1 + 5 * i] * 256);
    }
    unsigned int proctexid = AlphaTextureFromCharArray(proctex, div, div);

    std::cout << "posttexture" << std::endl;

    // Load terrain plane coords into vertex struct
    std::vector<vertex> newVertices;
    for(int i = 4; i < planeVertices.size(); i += 5)
    {
        vertex newVertex;
        newVertex.position = glm::vec3(planeVertices[i - 4], planeVertices[i - 3], planeVertices[i - 2]);
        newVertex.row = planeVertices[i - 1];
        newVertex.col = planeVertices[i];
        newVertices.push_back(newVertex);
    }

    // Create terrain plane mesh
    Mesh planeMesh = Mesh(newVertices, planeIndices);

    glEnable(GL_DEPTH_TEST);
    
    while(!glfwWindowShouldClose(window))
    {
        deltaTime = glfwGetTime() - lastFrame;
        lastFrame = glfwGetTime();

        processInput(window);

        glClearColor(0.52f, 0.8f, 0.91f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));

        shader.use();

        // View Transform
        int viewLoc = glGetUniformLocation(shader.ID, "view");
        glm::mat4 view = camera.GetViewMatrix();
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        
        // Projection Transform
        int projectionLoc = glGetUniformLocation(shader.ID, "projection");
        glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)windowWidth/(float)windowHeight, 0.1f, 500.0f);
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(proj));

        // bind texture TODO
        glBindTexture(GL_TEXTURE_2D, proctexid);

        // Model Transform
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -5.0f, 0.0f));
        int modelLoc = glGetUniformLocation(shader.ID, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

        // Draw terran plane
        planeMesh.Draw(shader);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }  
    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, 1);
    }
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(LEFT, deltaTime);
    }
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(RIGHT, deltaTime);
    }
    if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(UP, deltaTime);
    }
    if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(DOWN, deltaTime);
    }
}

void mouseCallback(GLFWwindow *window, double xpos, double ypos)
{
    float xOffset = xpos - lastX;
    float yOffset = ypos - lastY;

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xOffset, yOffset);
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}