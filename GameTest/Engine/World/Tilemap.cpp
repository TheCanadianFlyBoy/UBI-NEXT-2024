//Precompiled header
#include "stdafx.h"
//Self
#include "Tilemap.h"
//Math
#include <math.h>
#include <random>
//API
#include "../../App/app.h"
//Camera
#include "../Component/CameraComponent.h"
//Pathfinder
//#include "Pathfinder.h"


Tilemap::Tilemap(Vector2 InDimensions, Vector2 InTileSize)
    : TilemapDimensions(InDimensions), WorldUnitSize(InTileSize)
{
    //Copy types
    TileData = new Tile[4]{ {true,  Tilemap::TileType::Floor,  },
                                    {false, Tilemap::TileType::Wall, } };

    //Generate empty map
    Tiles = new char[int(InDimensions.x * InDimensions.y)] {0};
    //Pathfinder TemporaryPathfinder = Pathfinder(this);
    //Iterate entire map
    for (int i = 0; i < InDimensions.x * InDimensions.y; i++)
    {
        Vector2 TileCoords = ConvertIndexToMap(i);
        //Generate edge walls
        if (TileCoords.x == 0 || TileCoords.x == InDimensions.x - 1 || TileCoords.y == InDimensions.y - 1 || TileCoords.y == 0)
        {
            Tiles[i] = Wall;
        }
    }
    int PlayerStartX = 0;
    int PlayerStartY = 0;


    PlayerSpawn = Vector2(float(PlayerStartX), float(PlayerStartY));
    //Place barrier on level end
}

Tilemap::~Tilemap()
{
    //Erase tilemaps
    delete[] Tiles;
    delete[] TileData;
}



int Tilemap::GetTileIfWalkable(Vector2 InMapPosition)
{
    int index = ConvertMapToIndex(InMapPosition);
    return GetTileCostFromTilemapPosition(InMapPosition) != -1 ? index : -1;
}

Vector2 Tilemap::ConvertWorldtoMap(Vector2 InWorldPosition)
{
    InWorldPosition /= WorldUnitSize;
    InWorldPosition.x = floorf(InWorldPosition.x);
    InWorldPosition.y = floorf(InWorldPosition.y);
    return InWorldPosition;
}

int Tilemap::ConvertWorldtoIndex(Vector2 InWorldPosition)
{
    InWorldPosition /= WorldUnitSize;
    InWorldPosition.x = floor(InWorldPosition.x);
    InWorldPosition.y = floor(InWorldPosition.y);
    return ConvertMapToIndex(InWorldPosition);
}

Vector2 Tilemap::ConvertMaptoWorld(Vector2 InMapPosition, bool IsCentred)
{
    //TODO fix
    return IsCentred ? (InMapPosition) * (WorldUnitSize)+WorldUnitSize / 2 : Vector2(InMapPosition) * WorldUnitSize;
}

Vector2 Tilemap::ConvertIndextoWorld(int InIndex, bool IsCentred)
{
    return IsCentred ? ConvertMaptoWorld(ConvertIndexToMap(InIndex)) + WorldUnitSize / 2 : ConvertMaptoWorld(ConvertIndexToMap(InIndex));
}

Vector2 Tilemap::ConvertIndexToMap(int InIndex)
{
    return Vector2(float(InIndex % (int)floor(TilemapDimensions.x)), float(InIndex / (int)floor(TilemapDimensions.x)));
}

int Tilemap::ConvertMapToIndex(Vector2 InMapPosition)
{
    return (int)(floor(InMapPosition.y) * TilemapDimensions.x + floor(InMapPosition.x));
}

Vector2 Tilemap::GetTileCentre(Vector2 InMapPosition)
{
    return ConvertMaptoWorld(ConvertWorldtoMap(InMapPosition), true);
}

void Tilemap::Draw(CCamera* InCamera)
{
    float StartX = 0 - InCamera->GetCameraOrigin().x;
    float StartY = 0 - InCamera->GetCameraOrigin().y;
    float EndX = (TilemapDimensions.x * WorldUnitSize.x) - InCamera->GetCameraOrigin().x;
    float EndY = (TilemapDimensions.y * WorldUnitSize.y) - InCamera->GetCameraOrigin().y;                                                                          //TODO FIX THIS
    //TODO draw
    App::DrawLine(StartX, StartY, EndX, StartY, 1, 0, 0);
    App::DrawLine(StartX, EndY, EndX, EndY, 1, 0, 0);
    App::DrawLine(StartX, StartY, StartX, EndY, 1, 0, 0);
    App::DrawLine(EndX, StartY, EndX, EndY, 1, 0, 0);

    for (int i = 0; i < TilemapDimensions.x * TilemapDimensions.y; i++)
    {
        //Tile data
        StartX = ConvertIndextoWorld(i).x - InCamera->GetCameraOrigin().x;
        StartY = ConvertIndextoWorld(i).y - InCamera->GetCameraOrigin().y;
        EndX = StartX + WorldUnitSize.x;
        EndY = StartY + WorldUnitSize.y;
        float Color_R = 0.3f; float Color_G = 0.3f; float Color_B = 0.3f;
        Tile currenttile = GetTileTypeAtIndex(i);
        //DRAW GRID
        switch (currenttile.Type)
        {
        case Wall:
            StartX += 1;
            StartY += 1;
            EndX -= 1;
            EndY -= 1;
            Color_R = 1.0f;
            Color_G = 0.f;
            Color_B = 0.f;
            App::DrawLine(StartX, StartY, EndX, EndY, Color_R, Color_G, Color_B);
            App::DrawLine(EndX, StartY, StartX, EndY, Color_R, Color_G, Color_B);
            break;
        }
        App::DrawLine(StartX, StartY, EndX, StartY, Color_R, Color_G, Color_B);
        App::DrawLine(StartX, EndY, EndX, EndY, Color_R, Color_G, Color_B);
        App::DrawLine(StartX, StartY, StartX, EndY, Color_R, Color_G, Color_B);
        App::DrawLine(EndX, StartY, EndX, EndY, Color_R, Color_G, Color_B);
    }

}

void Tilemap::ReplaceTile(Vector2 InMapPosition, int InTileType)
{
    //Get index
    int index = ConvertMapToIndex(InMapPosition);
    //Get tile
    Tiles[index] = InTileType;
}


void Tilemap::GenerateWalls(int InType)
{
    //Calculate map size
    int IndexMax = int(TilemapDimensions.x * TilemapDimensions.y);
    //Get wall max and count
    int WallMax = IndexMax;
    int WallCount = 0;
    //Generate
    for (int i = 0; i < TilemapDimensions.x * TilemapDimensions.y; i++) {
        //Calculate coordinates
        Vector2 TileCoords = ConvertIndexToMap(i);
        switch (InType)
        {
        case 0:
            if ((fmod(TileCoords.x, 2) == 0 && fmod(TileCoords.y, 2) == 0 && WallCount < WallMax))
            {
                WallCount++;
                Tiles[i] = Wall;
            }
            break;
        }
    }



}

void Tilemap::GenerateObjectPosition(int& out_x, int& out_y)
{
    std::uniform_int_distribution<int> indexRandomizer{ 0, int((TilemapDimensions.y * TilemapDimensions.x) - 1) };
    //int index = indexRandomizer(m_Mersenne);
    //while (GetTileTypeAtIndex(index).Type != Floor)
    {
        //index = indexRandomizer(m_Mersenne); //TODO
    }
    //TileType tile = GetTileTypeAtIndex(index);
    //Vector2 output = ConvertIndexToMap(index);
    //out_x = output.x;
    //out_y = output.y;
}
