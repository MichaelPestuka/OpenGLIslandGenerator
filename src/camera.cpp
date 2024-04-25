#include "camera.hpp"

Camera::Camera(glm::vec3 position, glm::vec3 front, glm::vec3 up)
{
    Position = position;
    Front = front;
    WorldUp = up;
    Yaw = -90.0f;
    Pitch = 0.0f;
    UpdateCameraVectors();
}

void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
    float adjustedSpeed = defaultSpeed * deltaTime;
    if(direction == FORWARD)
    {
        Position += adjustedSpeed * Front;   
    }
    if(direction == LEFT)
    {
        Position -= adjustedSpeed * Right;   
    }
    if(direction == BACKWARD)
    {
        Position -= adjustedSpeed * Front;   
    }
    if(direction == RIGHT)
    {
        Position += adjustedSpeed * Right;   
    }
    if(direction == UP)
    {
        Position += adjustedSpeed * Up;   
    }
    if(direction == DOWN)
    {
        Position -= adjustedSpeed * Up;   
    }
    UpdateCameraVectors();
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset)
{
    xoffset *= defaultSensivity;
    yoffset *= defaultSensivity;

    Yaw += xoffset;
    Pitch -= yoffset;

    if(Pitch > 89.0f)
        Pitch = 89.0f;
    if(Pitch < -89.0f)
        Pitch = -89.0f;
    UpdateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix()
{
    return glm::lookAt(Position, Position + Front, Up);
}

void Camera::UpdateCameraVectors()
{
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front = glm::normalize(front);
    Right = glm::normalize(glm::cross(Front, WorldUp));
    Up = glm::normalize(glm::cross(Right, Front));
}