#include "dla.hpp"

// potential memory leak, resolve freeing original TODO
// TODO make into gaussian blur instead
mountain_point* ConvoluteBlur(mountain_point* original, int size, int mask_size, int passes)
{

    mountain_point *blurred = (mountain_point*)malloc(sizeof(mountain_point) * size * size);
    if(blurred == NULL)
    {
        std::cout << "Error allocating memory during blurring" << std::endl;
        return NULL;
    }
    for(int p = 0; p < passes; p++)
    {
        std::cout << "Blur pass " << p << std::endl;
        for(int x = 0; x < size; x++)
        {
            for (int y = 0; y < size; y++)
            {
                float heightSum = 0.0f;
                float tile_amount = 0.0f;
                for (int maskX = -mask_size; maskX <= mask_size; maskX++) // 5x5 blur mask
                {
                    for (int maskY = -mask_size; maskY <= mask_size; maskY++) // 5x5 blur mask
                    {
                        if(x + maskX < 0 || x + maskX >= size || y + maskY < 0 || y + maskY >= size)
                        {
                            continue;
                        }
                        heightSum += original[x + maskX + size * (y + maskY)].height;
                        tile_amount += 1.0f;    
                    }
                }
                blurred[x + size * y].height = heightSum / tile_amount;
            }
        }
        original = blurred;
    }
    return blurred;
}

// TODO make more space for valleys, maybe reuse for river generation?
mountain_point* GenerateBrownianTree(int size, float fill_amount)
{
    bool* map = (bool*)malloc(sizeof(bool) * size * size);
    mountain_point *ridges = (mountain_point*)malloc(sizeof(mountain_point) * size * size);
    if(map == NULL || ridges == NULL)
    {
        std::cout << "Error allocating memory for brownian tree" << std::endl;
        return NULL;
    }

    std::vector<mountain_point> endpoints;

    // Prevents indeterminant values in array
    for(int i = 0; i < size * size; i++)
    {
        map[i] = false;
        ridges[i].height = 0.35f;
    }

    float tiles_filled = 1.0f;
    float total_tiles = size * size;

    map[size / 2 + size * size / 2] = true;
    mountain_point midpoint = {size / 2, size / 2, 0, true, NULL};
    endpoints.push_back(midpoint);

    while (tiles_filled/total_tiles < fill_amount)
    {
        // std::cout << tiles_filled/total_tiles << std::endl;
        int x = rand() % size;
        int y = rand() % size;
        while(true)
        {
            if(x <= 0 || x >= size - 1 || y <= 0 || y >= size - 1)
            {
                // std::cout << "oob" << std::endl;
                break;
            }
            if(map[x - 1 + size * y] == true)
            {
                ridges[x + size * y].parent_point = &ridges[x - 1 + size * y];
                ridges[x - 1 + size * y].is_endpoint = false;

                // std::cout << "hit: " << x << ", " << y << std::endl;
                map[x + size * y] = true;
                ridges[x + size * y].height = 1.0f;
                tiles_filled += 1.0f;
                break;
            }
            if(map[x + 1 + size * y] == true)
            {
                ridges[x + size * y].parent_point = &ridges[x + 1 + size * y];
                ridges[x + 1 + size * y].is_endpoint = false;
                // std::cout << "hit: " << x << ", " << y << std::endl;
                map[x + size * y] = true;
                ridges[x + size * y].height = 1.0f;
                tiles_filled += 1.0f;
                break;
            }
            if(map[x + size * (y - 1)] == true)
            {
                ridges[x + size * y].parent_point = &ridges[x + 1 + size * (y - 1)];
                ridges[x + size * (y - 1)].is_endpoint = false;
                // std::cout << "hit: " << x << ", " << y << std::endl;
                map[x + size * y] = true;
                ridges[x + size * y].height = 1.0f;
                tiles_filled += 1.0f;
                break;
            }
            if(map[x + size * (y + 1)] == true)
            {
                ridges[x + size * y].parent_point = &ridges[x + 1 + size * (y + 1)];
                ridges[x + size * (y + 1)].is_endpoint = false;
                // std::cout << "hit: " << x << ", " << y << std::endl;
                map[x + size * y] = true;
                ridges[x + size * y].height = 1.0f;
                tiles_filled += 1.0f;
                break;
            }

            // can cause diagonal movement!

            x += rand() % 3 - 1;
            y += rand() % 3 - 1;
        }
    }
    mountain_point* blurred_ridges = ConvoluteBlur(ridges, size, 1, 2);
    return blurred_ridges;
}