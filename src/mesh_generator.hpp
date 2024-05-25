#ifndef MESH_GEN_H
#define MESH_GEN_H

#include <vector>
#include <iostream>
#include <random>
#include <queue>

#include <glm/glm.hpp>
#include "perlin_noise.hpp"

std::vector<float> PlaneVertices(int div, float size);

std::vector<int> PlaneIndices(int div);

enum coord_state {UNKNOWN, ENQUEUED, SEA, LAND};
#endif