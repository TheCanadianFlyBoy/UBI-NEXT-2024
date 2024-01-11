#pragma once
/*
*	CFB Engine - Tilemap
*	System for holding tile data for tile based collision
*
*/


//String
#include <string>
//Mersenne
#include <random>
//Vector
#include "../Math/Vector2.h"

class CCamera;

class Tilemap {
public: // Data Types
    enum TileType {
        Floor = 0,
        Wall
    };
    struct Tile {
        bool Walkable;
        TileType Type;
        //std::string SpriteName; //TODO implement
    };

public: //Common
    //Constructor
    Tilemap(Vector2 Dimensions, Vector2 TileSize);
    ~Tilemap();

    //Draw
    void Draw(class CCamera* Camera);

public: //Methods

    // Getters
    //Dimensions
    int GetHeight() { return (int)TilemapDimensions.y; };                 //TODO template?
    int GetWidth() { return (int)TilemapDimensions.x; };
    Vector2 GetDimensions() { return TilemapDimensions; };
    Vector2 GetTileSize() { return WorldUnitSize; };
    //Cost
    inline int GetTileCostFromTileIndex(int TileIndex)              { return (TileData[Tiles[TileIndex]].Walkable) ? 1 : -1; };
    inline int GetTileCostFromTilemapPosition(Vector2 MapPosition)  { return GetTileCostFromTileIndex(ConvertMapToIndex(MapPosition)); };
    inline int GetTileCostFromWorldPosition(Vector2 WorldPosition)  { return GetTileCostFromTileIndex(ConvertWorldtoIndex(WorldPosition)); };
    inline int GetTileIfWalkable(Vector2 MapPosition);
    //Type
    inline Tile GetTileTypeAtIndex(int Index) { return TileData[Tiles[Index]]; };
    //Preset Locations
    inline Vector2 GetPlayerStartWorld(bool Centred = false) { return ConvertMaptoWorld(PlayerSpawn, Centred); }
    inline Vector2 GetPlayerStartMap() { return PlayerSpawn; }


    //Conversions
    // World Conversion
    Vector2   ConvertWorldtoMap(Vector2 InWorldPosition);                              //Worldspace to Tilemap Vector
    int       ConvertWorldtoIndex(Vector2 InWorldPosition);                              //Worldspace to index
    //Tilemap Conversion
    Vector2   ConvertMaptoWorld(Vector2 InMapPosition, bool Centred = false);        //Tilemap vector to Worldspace
    int       ConvertMapToIndex(Vector2 InMapPosition);                              //Tilemap vector to index
    //Index Conversion
    Vector2   ConvertIndextoWorld(int Index, bool Centred = false);             //index to worldspace
    Vector2   ConvertIndexToMap(int Index);                                   //index to Tilemap vector     
    //Tile To Centre
    Vector2   GetTileCentre(Vector2 InMapPosition);                              //Returns a vector centred on nearest tile



    //Tile Updaters
    void ReplaceTile(Vector2 _tile_coordinate, int _tile_type);

    //Generation
    inline void GenerateRandomPosition(int& out_x, int& out_y) { GenerateObjectPosition(out_x, out_y); }
    inline Vector2 GenerateRandomWorldPosition() {
        int out_x = 0; int out_y = 0;
        GenerateObjectPosition(out_x, out_y);
        return ConvertMaptoWorld(Vector2(float(out_x), float(out_y)), true);
    }
    void GenerateWalls(int type);
    inline static int GetDefaultTilesCount() { return 4; }



protected: //members
    //Tiles
    char* Tiles;
    Tile* TileData;

    //Dimensions
    Vector2 TilemapDimensions; // ROWS AND COLUMNS
    Vector2 WorldUnitSize;      //ACTUAL TILE SIZE

    //Game data
    Vector2 PlayerSpawn;

    //Random generation
    //std::mt19937& m_Mersenne;
    void GenerateObjectPosition(int& out_x, int& out_y);
};