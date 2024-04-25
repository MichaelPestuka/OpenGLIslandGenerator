#include "mesh_generator.hpp"

std::vector<float> PlaneVertices(int div, float size)
{
    std::vector<float> plane;

    float triangle_size = size/div; 
    for (int row = 0; row < div; row++)
    {
        for (int col = 0; col < div; col++)
        {
            glm::vec3 vertexPosition = glm::vec3(col * triangle_size, 0.0, row * triangle_size);
            plane.push_back(vertexPosition.x);
            plane.push_back(vertexPosition.y);
            plane.push_back(vertexPosition.z);

            plane.push_back((float)col);
            plane.push_back((float)row);

            // std::cout << "pos: " << vertexPosition.x << ", " << vertexPosition.y << ", "<< vertexPosition.z << std::endl;
        }
    }
    return plane;
    
}

std::vector<int> PlaneIndices(int div)
{
    std::vector<int> indices;
    for (int row = 0; row < div; row++)
    {
        for (int col = 0; col < div; col++)
        {
            int index = row * (div + 1) + col;

            indices.push_back(index);
            indices.push_back(index + 1);
            indices.push_back(index + div + 1);
            
            indices.push_back(index + 1);
            indices.push_back(index + div + 1);
            indices.push_back(index + div + 2);
        }
        
    }
    return indices; 
}