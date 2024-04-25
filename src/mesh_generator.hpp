#ifndef MESH_GEN_H
#define MESH_GEN_H

#include <vector>
#include <iostream>

#include <glm/glm.hpp>

std::vector<float> PlaneVertices(int div, float size);

std::vector<int> PlaneIndices(int div);
#endif