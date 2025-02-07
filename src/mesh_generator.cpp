#include "mesh_generator.hpp"
#include <cstdint>

std::vector<float> PlaneVertices(int div, float size, bool use_perlin = true)
{
    std::vector<float> plane;
    PerlinNoise noise = PerlinNoise(0, 0.05f, 4, 1.0f);

    float triangle_size = size/div; 
    float heights[div][div];

    if(use_perlin)
    {

        for (int row = 0; row < div; row++)
        {
            for (int col = 0; col < div; col++)
            {
                float circle_placement = pow((col - div/2), 2) + pow((row - div/2), 2);
                circle_placement /= pow(div/2, 2);
                circle_placement *= -1.0f;
                circle_placement += 1.0f;
                std::clamp(circle_placement, 0.0f, 1.0f);

                heights[row][col] = circle_placement * (1.0f + noise.FractalValue(row, col)) / 2.0f;
            }
        }

        std::cout << "hgen" << std::endl;

        coord_state is_sea[div][div]; 
        is_sea[1][1] = SEA;
        std::queue<glm::ivec2> unchecked_coords;
        unchecked_coords.push(glm::ivec2(1, 1));
        while(!unchecked_coords.empty())
        {
            glm::ivec2 coord = unchecked_coords.front();
            unchecked_coords.pop();
            if(heights[coord.x][coord.y] < 0.4f)
            {
                is_sea[coord.x][coord.y] = SEA;
                
                if(coord.x > 0 && is_sea[coord.x - 1][coord.y] == UNKNOWN)
                {
                    unchecked_coords.push(glm::ivec2(coord.x - 1, coord.y));
                    is_sea[coord.x - 1][coord.y] = ENQUEUED;
                }
                if(coord.x < div - 1 && is_sea[coord.x + 1][coord.y] == UNKNOWN)
                {
                    unchecked_coords.push(glm::ivec2(coord.x + 1, coord.y));
                    is_sea[coord.x + 1][coord.y] = ENQUEUED;
                }
                if(coord.y > 0 && is_sea[coord.x][coord.y - 1] == UNKNOWN)
                {
                    unchecked_coords.push(glm::ivec2(coord.x, coord.y - 1));
                    is_sea[coord.x][coord.y - 1] = ENQUEUED;
                }
                if(coord.y < div - 1 && is_sea[coord.x][coord.y + 1] == UNKNOWN)
                {
                    unchecked_coords.push(glm::ivec2(coord.x, coord.y + 1));
                    is_sea[coord.x][coord.y + 1] = ENQUEUED;
                }
            }
            else
            {
                is_sea[coord.x][coord.y] = LAND;
            }
        }
        std::cout << "seastate" << std::endl;
        for (int row = 0; row < div; row++)
        {
            for (int col = 0; col < div; col++)
            {
                if(is_sea[row][col] == UNKNOWN && heights[row][col] < 0.4f)
                {
                    heights[row][col] = 0.4f;
                }
            }
        }
        std::cout << "flatten" << std::endl;
    }

    // Generating vertex heights using DLA algo
    else
    {
        Map map(div);        
        // map.GenerateIslandShape();
        map.GenerateMountainRidges(0.05f);
        map.BoxBlurMap(1, 20);

        for (int row = 0; row < div; row++)
        {
            for (int col = 0; col < div; col++)
            {
                // std::cout << map.GetTile(row, col)->GetHeight() << std::endl;
                heights[row][col] = map.GetTile(row, col)->GetHeight();
            }
        }
    }
    for (int row = 0; row < div; row++)
    {
        for (int col = 0; col < div; col++)
        {

            glm::vec3 vertexPosition = glm::vec3(col * triangle_size, heights[row][col] , row * triangle_size);
            plane.push_back(vertexPosition.x);
            plane.push_back(vertexPosition.y);
            plane.push_back(vertexPosition.z);

            plane.push_back((float)row);
            plane.push_back((float)col);


            // std::cout << "pos: " << vertexPosition.x << ", " << vertexPosition.y << ", "<< vertexPosition.z << std::endl;
        }
    }
    return plane;
    
}

std::vector<uint32_t> PlaneIndices(int div)
{
    std::vector<uint32_t> indices;
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