#include "stdafx.h"
#include "Quadtree.h"

/// <summary>
/// Inserts a given node into the quad tree
/// </summary>
/// <param name="InNode">Node to insert</param>
void QuadTree::InsertNode(std::shared_ptr<QuadNode> InNode)
{
	//Null / boundary check
	if (!InNode || !IsInBoundary(InNode->Position)) return;

	//Check for space
	if (abs(TopLeft.x - BottomRight.x) <= 1 && (TopLeft.y - BottomRight.y) <= 1)
	{	//Case 1, current quadrant
		//Empty node, save
		if (Node == nullptr)
			Node = InNode;
		return;
	}

	int MidX = (TopLeft.x + BottomRight.x) / 2;
	int MidY = (TopLeft.y + BottomRight.y) / 2;

	//Figure out which tree to use
	if (MidX >= InNode->Position.x) // Left side
	{
		if (MidY >= InNode->Position.y) // Top side
		{
			//If our branch to the top left is null, make a new one
			if (TopLeftTree == nullptr)
			{
				//Top left sector
				TopLeftTree = std::make_shared<QuadTree>(
					QuadPoint(TopLeft.x, TopLeft.y),
					QuadPoint(MidX, MidY));
				//Recurse
				TopLeftTree->InsertNode(InNode);
			}
		}
		else { //Bottom side
			if (BottomLeftTree == nullptr)
			{
				//Bottom left sector
				BottomLeftTree = std::make_shared<QuadTree>(
					QuadPoint(TopLeft.x, MidY),
					QuadPoint(MidX, BottomRight.y));
				//Recurse
				BottomLeftTree->InsertNode(InNode);
			}
		}
	}
	else //Right side
	{
		//Top side
		if (MidY >= InNode->Position.y)
		{
			//If our branch to the top right is null, make a new one
			if (TopRightTree == nullptr)
			{
				//Top Right sector
				TopRightTree = std::make_shared<QuadTree>(
					QuadPoint(MidX, TopLeft.y),
					QuadPoint(BottomRight.x, MidY));
				//Recurse
				TopRightTree->InsertNode(InNode);
			}
		}
		else
		{
			//If our branch to the bottom right is null, make a new one
			if (BottomRightTree == nullptr)
			{
				//Bottom left sector
				BottomRightTree = std::make_shared<QuadTree>(
					QuadPoint(MidX, MidY),
					QuadPoint(BottomRight.x, BottomRight.y));
				//Recurse
				BottomRightTree->InsertNode(InNode);
			}
		}
	}

}

std::shared_ptr<QuadNode> QuadTree::FindNodeAtPoint(QuadPoint InPoint)
{
	// Null / boundary check
	if (!IsInBoundary(InPoint)) return nullptr;

	if (Node) return Node;

	int MidX = (TopLeft.x + BottomRight.x) / 2;
	int MidY = (TopLeft.y + BottomRight.y) / 2;

	if (MidX >= InPoint.x) //Left side
	{
		if (MidY >= InPoint.y) //Top side
		{
			//Check that branch if it exists
			if (!TopLeftTree) return nullptr;
			return TopLeftTree->FindNodeAtPoint(InPoint);
		}
		else //Bottom side
		{
			//Check that branch if it exists
			if (!BottomLeftTree) return nullptr;
			return BottomLeftTree->FindNodeAtPoint(InPoint);
		}
	}
	else // Right Side
	{
		if (MidY >= InPoint.y) //Top side
		{
			//Check that branch if it exists
			if (!TopRightTree) return nullptr;
			return TopRightTree->FindNodeAtPoint(InPoint);
		}
		else // Bottom side
		{
			//Check that branch if it exists
			if (!BottomRightTree) return nullptr;
			return BottomRightTree->FindNodeAtPoint(InPoint);
		}
	}
}

bool QuadTree::IsInBoundary(QuadPoint InPoint)
{
	return InPoint.x >= TopLeft.x && InPoint.x <= BottomRight.x && InPoint.y >= TopLeft.y && InPoint.y <= BottomRight.y;
}

void QuadTreeUnitTest()
{

	//Create a tree
	std::shared_ptr<QuadTree> Root = std::make_shared<QuadTree>(QuadPoint(0, 0), QuadPoint(40, 40));
	std::shared_ptr<QuadNode> g;

	//Insertion test
	Root->InsertNode(std::make_shared<QuadNode>(QuadPoint(4, 4), 1));
	Root->InsertNode(std::make_shared<QuadNode>(QuadPoint(5, 4), 2));
	Root->InsertNode(std::make_shared<QuadNode>(QuadPoint(10, 14), 3));
	Root->InsertNode(std::make_shared<QuadNode>(QuadPoint(40, 48), 4));

	//Search Test
	g = Root->FindNodeAtPoint(QuadPoint(4, 4));
	g = Root->FindNodeAtPoint(QuadPoint(5, 5));
	g = Root->FindNodeAtPoint(QuadPoint(30, 30));
	g = Root->FindNodeAtPoint(QuadPoint(50, 50));



}
