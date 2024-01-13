#pragma once
//std::vector
#include <vector>
//Vector2
#include "../Math/Vector2.h"

struct PathNode
{
    enum class PathNodeStatus
    {
        Unchecked,
        Open,
        Closed,
    };

    int ParentNodeIndex;
    PathNodeStatus Status;

    float NodeCost;      // Cost to get to this node.
    float Heuristic; // Heuristic: manhatten distance to destination.
    float FinalCost; // Sum of the 2 values above.
};

class Pathfinder
{
protected:
    //Map of tiles
    class Tilemap* PathMap;
    //Map dimensions
    int PathMapWidth;
    int PathMapHeight;
    //Nodes
    std::vector<PathNode> PathNodes;

public:
    Pathfinder(Tilemap* InTilemap);
    virtual ~Pathfinder();

    // Start a search, supply the starting tile x,y and ending tile x,y.
    // Returns true if path found, false otherwise.
    bool FindPath(int StartX, int StartY, int EndX, int EndY);

    //Gets the dimensions of the path map
    Vector2 GetDimensions();

    // Retrieve the final path.
    std::vector<int> GetPath(int EndX, int EndY);

    //Clear all path nodes
    void ClearPath();
};