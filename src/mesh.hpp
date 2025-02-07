#ifndef MESH_H
#define MESH_H

#include <vector>

#include "shader.hpp"

#include <glm/glm.hpp>

struct vertex {
    glm::vec3 position;
    float row;
    float col;
};

class Mesh {
    public:
        std::vector<vertex> vertices;
        std::vector<uint32_t> indices;
        Mesh(std::vector<vertex> vertices, std::vector<uint32_t> indices);
        void Draw(Shader shader);
    private:
        uint32_t VAO, VBO, EBO;
        void setupMesh();

};

#endif
