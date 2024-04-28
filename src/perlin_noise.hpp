#ifndef PERLIN_NOISE_H
#define PERLIN_NOISE_H

#include <vector>
#include <iostream>
#include <algorithm>
#include <glm/glm.hpp>
#include <glm/vec2.hpp>

class PerlinNoise
{
    public:
        PerlinNoise(int seed, float frequency, int octaves, float amplitude);
        float GetValue(float x, float y);
        float FractalValue(float x, float y);
    private:
        int seed;
        float frequency;
        int octaves;
        float amplitude;
        std::vector<int> permutation;
        std::vector<int> Shuffle(std::vector<int> toShuffle);
        void MakePermutation();
        glm::vec2 GetConstantVector(int v);
        float Lerp(float t, float a, float b);
        float Fade(float t);
};

#endif