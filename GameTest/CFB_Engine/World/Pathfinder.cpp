//Precompiled header
#include "stdafx.h"
//Self
#include "Pathfinder.h"
//Tilemap
#include "Tilemap.h"

//For easier shorthand
typedef PathNode::PathNodeStatus PathNodeStatus;


Pathfinder::Pathfinder(Tilemap* InTilemap)
{
    PathMap = InTilemap;
    PathMapWidth = InTilemap->GetWidth();
    PathMapHeight = InTilemap->GetHeight();

    PathNodes.resize(PathMapWidth * PathMapHeight);
}

Pathfinder::~Pathfinder()
{
}

bool Pathfinder::FindPath(int sx, int sy, int ex, int ey)
{
    //CATCH: unwalkable ending node/starting node
    if (PathMap->GetTileCostFromTileIndex(ex + ey * PathMapWidth) == -1)
    {
        return false;
    }

    //Reset all nodes
    ClearPath();

    std::vector<int> OpenIndicies;

    //Get initial node
    float cost = 0;
    float heuristic = fabsf((float)(ex - sx)) + fabsf((float)(ey - sy));
    float finalCost = heuristic + cost;
    int parent = sx + sy * PathMapWidth;
    //Create node
    PathNode FirstNode = PathNode{ parent, PathNode::PathNodeStatus::Open, cost, heuristic, finalCost };
    PathNode FinalNode = PathNode{ ex + ey * PathMapWidth, PathNodeStatus::Unchecked, heuristic, cost, finalCost };
    OpenIndicies.push_back(FirstNode.ParentNodeIndex);
    PathNodes[FirstNode.ParentNodeIndex] = FirstNode;

    //LOOP
    while (!OpenIndicies.empty())
    {
        //Get open node
        int OpenNodeIndex = 0;
        int DeletionIndex = 0;
        //Iterate to find lowest F score
        for (int i = 0; i < OpenIndicies.size(); i++)
        {
            //Get current node
            PathNode& current_node = PathNodes[OpenIndicies[i]];
            PathNode& open_node = PathNodes[OpenNodeIndex];
            if (current_node.FinalCost <= open_node.FinalCost)
            {
                //Set current node to open node
                OpenNodeIndex = OpenIndicies[i];
                DeletionIndex = i;
            }
        }
        //Delete        
        OpenIndicies.erase(OpenIndicies.begin() + DeletionIndex);

        //If end point, return true!
        if (OpenNodeIndex == ex + ey * PathMapWidth)
        {
            return true;
        }

        //Mark closed
        PathNodes[OpenNodeIndex].Status = PathNodeStatus::Closed;

        //Add neighbours
        int node_x = OpenNodeIndex % PathMap->GetWidth();
        int node_y = OpenNodeIndex / PathMap->GetWidth();

        int neighbours[4] = {   PathMap->GetTileIfWalkable(Vector2(node_x + 1, node_y )),
                                PathMap->GetTileIfWalkable(Vector2(node_x - 1, node_y )),
                                PathMap->GetTileIfWalkable(Vector2(node_x, node_y + 1 )),
                                PathMap->GetTileIfWalkable(Vector2(node_x, node_y - 1 )) };
        //Loop neighbours
        for (int i = 0; i < 4; i++)
        {
            //Is valid
            if (neighbours[i] != -1 && PathNodes[neighbours[i]].Status != PathNodeStatus::Closed)
            {
                //Get coords
                int neighbour_x = neighbours[i] % PathMap->GetWidth();
                int neighbour_y = neighbours[i] / PathMap->GetWidth();
                //Check if in list already
                bool add = true;
                for (int j = 0; j < OpenIndicies.size(); j++)
                {
                    if (OpenIndicies[j] == neighbours[i]) add = false; //Is in list, do not add
                }
                //Push
                if (add) OpenIndicies.push_back(neighbours[i]);
                //Calculate g
                float cost = PathNodes[OpenNodeIndex].NodeCost + 1.f;
                float heuristic = fabsf((float)(ex - neighbour_x)) + fabsf((float)(ey - neighbour_y));
                float finalCost = cost + heuristic;
                PathNodes[neighbours[i]].NodeCost = cost;
                PathNodes[neighbours[i]].Heuristic = heuristic;
                PathNodes[neighbours[i]].FinalCost = finalCost;
                PathNodes[neighbours[i]].ParentNodeIndex = OpenNodeIndex;
            }
        }
    }


    return false;
}

Vector2 Pathfinder::GetDimensions()
{
    return Vector2(PathMapWidth, PathMapHeight);
}

std::vector<int> Pathfinder::GetPath(int ex, int ey)
{
    //Create vector of indicies
    std::vector<int> path;

    //Get end node index and add to path
    int current_node_index = ex + ey * PathMap->GetWidth();
    path.push_back(current_node_index);
    //Iterate the parents
    while (PathNodes[current_node_index].ParentNodeIndex != current_node_index)
    {
        PathNode& current_node = PathNodes[current_node_index];
        int parent = current_node.ParentNodeIndex;
        //Add to path
        path.push_back(parent);
        //Rejazzle the shmazzle
        current_node_index = parent;
    }


    return path;
}

void Pathfinder::ClearPath()
{
    //Reset all nodes
    for (int i = 0; i < PathNodes.size(); i++)
    {
        PathNode& _node = PathNodes[i];
        _node.NodeCost = FLT_MAX;
        _node.Heuristic = FLT_MAX;
        _node.FinalCost = FLT_MAX;
        _node.ParentNodeIndex = i;
        _node.Status = PathNodeStatus::Unchecked;
    }
}
