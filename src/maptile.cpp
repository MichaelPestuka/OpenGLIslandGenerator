#include "maptile.hpp"

MapTile::MapTile(int x, int y)
{
    this->x = x;
    this->y = y;
    this->parentTile = nullptr;
    this->height = 0.35f;
}

void MapTile::SetHeight(float height)
{
    this->height = height;
}

float MapTile::GetHeight()
{
    return this->height;
}

void MapTile::SetParent(MapTile* parent)
{
    this->parentTile = parent;
}

MapTile* MapTile::GetParent()
{
    return this->parentTile;
}

void MapTile::SetType(TileType type)
{
    this->type = type;
}

TileType MapTile::GetType()
{
    return this->type;
}

SegmentType MapTile::GetSegmentType()
{
    return this->segment_type;
}

void MapTile::SetSegmentType(SegmentType endpoint)
{
    this->segment_type = endpoint;
}

int MapTile::GetDistanceFromEnd()
{
    return this->distance_from_end;
}

void MapTile::SetDistanceFromEnd(int distance)
{
    this->distance_from_end = distance;
}