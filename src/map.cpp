#include "map.hpp"

Map::Map(int size)
{
    this->size = size;
    tiles = {};
    for (int i = 0; i < size*size; i++)
    {
        tiles.push_back(MapTile(i % size, i / size));
    }
    
}

MapTile* Map::GetTile(int x, int y)
{
    if(&(tiles[x+size*y]) == nullptr)
    {
        std::cout << "nonexist: " << x << " " << y << std::endl;
    }
    return &(tiles[x + size*y]);
}

void Map::GenerateIslandShape()
{
    PerlinNoise noise = PerlinNoise(0, 0.01f, 4, 1.0f);
    for (int x = 0; x < size; x++)
    {
        for (int y = 0; y < size; y++)
        {
            float circle_placement = pow((x - size/2), 2) + pow((y - size/2), 2);
            circle_placement /= pow(size/2, 2);
            circle_placement *= -1.0f;
            circle_placement += 1.0f;
            circle_placement *= noise.FractalValue(x, y);
            std::clamp(circle_placement, 0.0f, 1.0f);
            GetTile(x, y)->SetHeight(circle_placement);
        }
    }
}

void Map::GenerateMountainRidges(float map_fill_amount)
{
    float current_tiles_filled = 0.0f;
    float total_tiles = size*size;

    GetTile(size/2, size/2)->SetType(TileType::RIDGE);
    GetTile(size/2, size/2)->SetSegmentType(SegmentType::START);

    while (current_tiles_filled/total_tiles < map_fill_amount)
    {
        int x = 0;
        int y = 0;
        int rand_val = rand() % 4;
        if(rand_val == 0)
        {
            x = 1;    
            y = rand() % size;
        }
        else if(rand_val == 1)
        {
            x = size - 2;    
            y = rand() % size;
        }
        else if(rand_val == 2)
        {
            x = rand() % size;    
            y = 1;
        }
        else if(rand_val == 3)
        {
            x = rand() % size;    
            y = size - 2;
        }

        while(true)
        {
            if(x <= 0 || x >= size - 1 || y <= 0 || y >= size - 1)
            {
                break;
            }
            MapTile *new_parent = NULL;
            if(GetTile(x - 1, y)->GetType() == TileType::RIDGE)
            {
                new_parent = GetTile(x - 1, y);
            }
            if(GetTile(x + 1, y)->GetType() == TileType::RIDGE)
            {
                new_parent = GetTile(x + 1, y);
            }
            if(GetTile(x, y - 1)->GetType() == TileType::RIDGE)
            {
                new_parent = GetTile(x, y - 1);
            }
            if(GetTile(x, y + 1)->GetType() == TileType::RIDGE)
            {
                new_parent = GetTile(x, y + 1);
            }

            if(new_parent != NULL)
            {
                current_tiles_filled += 1.0f;
                GetTile(x, y)->SetType(TileType::RIDGE);
                GetTile(x, y)->SetParent(new_parent);
                GetTile(x, y)->SetSegmentType(SegmentType::END);
                if(new_parent->GetSegmentType() != SegmentType::START)
                {
                    new_parent->SetSegmentType(SegmentType::MID);
                }
                break;
            }
            int dir = rand() % 4;
            if(dir == 0)
            {
                x += 1;
            }
            else if(dir == 1)
            {
                x -= 1;
            }
            else if(dir == 2)
            {
                y += 1;
            }
            else if(dir == 3)
            {
                y -= 1;
            }
        }
    }

    int amt = 0;
    for (int x = 0; x < size; x++)
    {
        for (int y = 0; y < size; y++)
        {
            if(GetTile(x, y)->GetSegmentType() == SegmentType::END && GetTile(x, y)->GetType() == TileType::RIDGE)
            {
                int i = 0;
                MapTile* current_tile = GetTile(x, y);
                int current_distance = 0;
                while(current_tile->GetSegmentType() != SegmentType::START)
                {
                    if(current_tile->GetDistanceFromEnd() > current_distance)
                    {
                        break;
                    }
                    current_tile->SetDistanceFromEnd(current_distance);
                    current_distance += 1;
                    current_tile->SetHeight(std::max(1.0f - 1.0f/(1.0f + current_distance), current_tile->GetHeight()));
                    current_tile = current_tile->GetParent();
                    if(i > size * 10)
                    {
                        std::cout << "Probable loop in ridge generation!" << std::endl;
                        break;
                    }
                    i++;
                }
            }
        }
            
    }
    
}

void Map::BoxBlurMap(int mask_size, int passes)
{
    float* new_heights = (float*)malloc(size*size*sizeof(float));
    for (int i = 0; i < passes; i++)
    {
        for (int x = 0; x < size; x++)
        {
            for (int y = 0; y < size; y++)
            {
                float sum_height = 0.0f;
                float tile_count = 0.0f;
                for (int xl = -mask_size; xl <= mask_size; xl++)
                {
                    for (int yl = -mask_size; yl <= mask_size; yl++)
                    {
                        if(x + xl < 0 || x + xl >= size || y + yl < 0 || y + yl >= size)
                        {
                            continue;
                        }
                        sum_height += GetTile(x + xl, y + yl)->GetHeight();
                        tile_count += 1.0f;
                    }
                }
                // std::cout << "avg output: " << sum_height << " / " << tile_count << std::endl;
                new_heights[x + size*y] = sum_height/tile_count;
            
            }
        }
        for (int x = 0; x < size; x++)
        {
            for (int y = 0; y < size; y++)
            {
                if(GetTile(x, y)->GetType() == TileType::RIDGE)
                {
                    if(GetTile(x, y)->GetHeight() > new_heights[x + size*y])
                    {
                        continue;
                    }
                }
                GetTile(x, y)->SetHeight(new_heights[x + size*y]);
            }
        }
    }
}

void Map::GenerateRivers(int amount)
{

}

std::vector<struct coordinate> Map::PathfindRiver(struct coordinate start, struct coordinate end)
{
    std::vector<struct coordinate> path;
    // std::vector<struct coordinate> path;
    // std::vector<struct coordinate> path;
    
}