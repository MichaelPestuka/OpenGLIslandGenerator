#ifndef H_MAP
#define H_MAP

#include "maptile.hpp"
#include "perlin_noise.hpp"
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <math.h>

struct coordinate {
    int x;
    int y;
};

class Map
{
    public:
        Map(int size);
        MapTile* GetTile(int x, int y);
        void GenerateIslandShape();
        void GenerateMountainRidges(float map_fill_amount);
        void BoxBlurMap(int mask_size, int passes);
        void GenerateRivers(int amount);
    private:
        int size;
        std::vector<MapTile> tiles;
        void FillInGapsInNoise();
        bool compareDistance(struct coordinate a, struct coordinate b);
        std::vector<struct coordinate> PathfindRiver(struct coordinate start, struct coordinate end);
};

#endif