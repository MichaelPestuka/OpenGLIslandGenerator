#ifndef MESH_GEN_H
#define MESH_GEN_H

#include <vector>
#include <iostream>
#include <random>
#include <queue>

#include <glm/glm.hpp>
#include "perlin_noise.hpp"
#include "map.hpp"
#include "maptile.hpp"

std::vector<float> GenerateHeightmap(int div, bool use_perlin);

std::vector<float> PlaneVertices(std::vector<float> heights, int div, float size);

std::vector<uint32_t> PlaneIndices(int div);

enum coord_state {UNKNOWN, ENQUEUED, SEA, LAND};
#endif