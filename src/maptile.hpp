#ifndef H_MAPTILE
#define H_MAPTILE

enum TileType {LANDTILE, RIVER, RIDGE};

enum SegmentType {START, MID, END};

class MapTile
{
    public:
        MapTile(int x, int y);
        int x;
        int y;
        void SetHeight(float height);
        void SetParent(MapTile* parent);
        void SetType(TileType type);
        TileType GetType();
        float GetHeight();
        MapTile* GetParent();
        
        int GetDistanceFromEnd();
        void SetDistanceFromEnd(int distance);

        SegmentType GetSegmentType();
        void SetSegmentType(SegmentType endpoint);

    private:
        SegmentType segment_type;
        float height = 0.0f;
        int distance_from_end;
        TileType type;
        MapTile* parentTile;
};

#endif