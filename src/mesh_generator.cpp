#include "mesh_generator.hpp"

std::vector<float> PlaneVertices(int div, float size)
{
    std::vector<float> plane;
    PerlinNoise noise = PerlinNoise(0, 0.05f, 4, 1.0f);

    float triangle_size = size/div; 
    for (int row = 0; row < div; row++)
    {
        for (int col = 0; col < div; col++)
        {
            
            glm::vec3 vertexPosition = glm::vec3(col * triangle_size, (1.0f + noise.FractalValue(col, row)) / 2.0f, row * triangle_size);
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
    for (int row = 0; row < div - 1; row++)
    {
        for (int col = 0; col < div - 1; col++)
        {
            int index = row * div + col;

            indices.push_back(index);
            indices.push_back(index + 1);
            indices.push_back(index + div);
            // std::cout << "tri: " << index << ", " << index + 1 << ", " << index + div << std::endl;
            indices.push_back(index + 1);
            indices.push_back(index + div);
            indices.push_back(index + div + 1);
        }
        
    }
    return indices; 
}