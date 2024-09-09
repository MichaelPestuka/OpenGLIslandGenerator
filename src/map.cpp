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
                    current_tile->SetHeight(1.0f - 1.0f/(1.0f + current_distance));
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

void Map::GaussianBlurMap(int mask_size, int passes)
{

}