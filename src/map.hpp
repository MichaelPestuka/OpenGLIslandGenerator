#include "maptile.hpp"
#include <stdlib.h>
#include <iostream>
#include <vector>

class Map
{
    public:
        Map(int size);
        MapTile* GetTile(int x, int y);
        void GenerateMountainRidges(float map_fill_amount);
        void GaussianBlurMap(int mask_size, int passes);
    private:
        int size;
        std::vector<MapTile> tiles;
};