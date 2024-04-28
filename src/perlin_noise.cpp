#include "perlin_noise.hpp"

PerlinNoise::PerlinNoise(int seed, float frequency, int octaves, float amplitude)
{
    this->seed = seed;
    this->frequency = frequency;
    this->octaves = octaves;
    this->amplitude = amplitude;
    MakePermutation();
}

void PerlinNoise::MakePermutation()
{
    for (int i = 0; i < 256; i++)
    {
        permutation.push_back(i);        
    }
    
    std::random_shuffle(permutation.begin(), permutation.end());

    for (int i = 0; i < 256; i++)
    {
        permutation.push_back(permutation[i]); // Doubling the permutation
    }
}

glm::vec2 PerlinNoise::GetConstantVector(int v)
{
    v = v % 4;
    if(v == 0)
    {
        return glm::vec2(1.0f, 1.0f);
    }
    if(v == 1)
    {
        return glm::vec2(-1.0f, 1.0f);
    }
    if(v == 2)
    {
        return glm::vec2(-1.0f, -1.0f);
    }
    else
    {
        return glm::vec2(1.0f, -1.0f);
    }
}

float PerlinNoise::Lerp(float t, float a, float b)
{
    return a + t *(b - a);
}

float PerlinNoise::Fade(float t)
{
    return 6 * pow(t, 5) - 15 * pow(t ,4) + 10 * pow(t, 3);
}

float PerlinNoise::FractalValue(float x, float y)
{
    float result = 0.0f;
    float local_frequency = frequency;
    float local_amplitude = amplitude;
    for (int octave = 0; octave < octaves; octave++)
    {
        float n = local_amplitude * GetValue(x * local_frequency, y * local_frequency);
        result += n;
        // std::cout << "oct: " << octave << " result prog: " << x * frequency << std::endl;
        local_amplitude *= 0.5f;
        local_frequency *= 2.0f;
    }
    // std::cout << "x: " << x << " y: " << y << " result: " << result << std::endl;
    return result;
}

float PerlinNoise::GetValue(float x, float y)
{

    int X = (int)x % 255;
    int Y = (int)y % 255;

    float xf = x - floor(x);
    float yf = y - floor(y);


    glm::vec2 topRight = glm::vec2(xf-1.0f, yf-1.0f);
    glm::vec2 topLeft = glm::vec2(xf, yf-1.0f);
    glm::vec2 bottomRight = glm::vec2(xf-1.0f, yf);
    glm::vec2 bottomLeft = glm::vec2(xf, yf);

    int valueTopRight = permutation[permutation[X + 1] + Y + 1];
    int valueTopLeft = permutation[permutation[X] + Y + 1];
    int valueBottomRight = permutation[permutation[X + 1] + Y];
    int valueBottomLeft = permutation[permutation[X] + Y];

    float dotTopRight = glm::dot(topRight, PerlinNoise::GetConstantVector(valueTopRight));
    float dotTopLeft = glm::dot(topLeft, PerlinNoise::GetConstantVector(valueTopLeft));
    float dotBottomRight = glm::dot(bottomRight, PerlinNoise::GetConstantVector(valueBottomRight));
    float dotBottomLeft = glm::dot(bottomLeft, PerlinNoise::GetConstantVector(valueBottomLeft));

    float u = PerlinNoise::Fade(xf);
    float v = PerlinNoise::Fade(yf);


    float result = Lerp(u, Lerp(v, dotBottomLeft, dotTopLeft), Lerp(v, dotBottomRight, dotTopRight));
    //std::cout << "x: " << x << " y: " << y << " result: " << result << std::endl;
    return result;
}
