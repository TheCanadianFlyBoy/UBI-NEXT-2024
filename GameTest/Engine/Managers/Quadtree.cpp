#include "stdafx.h"
#include "Quadtree.h"
#include "../Object/Actor.h"

void QuadTree::AddObject(std::shared_ptr<Actor> InActor) //TODO ref?
{
	//Case 1: Insert into vector
	if (Objects.size() < QUAD_MAX_CHILDREN)
	{
		Objects.push_back(InActor);
	}
	else //Case 2: split leaf node
	{
		//Push into array
		Objects.push_back(InActor);
		//Now split
		Split();
	}
}

void QuadTree::Split()
{
	//Only allowed on leaves
	assert(IsLeaf());

	//Get centre point
	Vector2 MidPoint = (TopLeft + BottomRight) / 2;

	//Force child nodes
	TopLeftTree			= std::make_shared<QuadTree>(TopLeft, MidPoint);
	TopRightTree		= std::make_shared<QuadTree>(Vector2(MidPoint.x, TopLeft.y), Vector2(BottomRight.x, MidPoint.y));
	BottomLeftTree		= std::make_shared<QuadTree>(Vector2(TopLeft.x, MidPoint.y), Vector2(MidPoint.x, BottomRight.y));
	BottomRightTree		= std::make_shared<QuadTree>(MidPoint, BottomRight);

	//smart pointer ref
	for (std::shared_ptr<Actor>& Child : Objects)
	{
		//Reinsert everything
		InsertNode(Child->GetActorLocation(), Child);
	}

	//Clear vector
	Objects.clear();

}

QuadTree::~QuadTree()
{
	Objects.clear();

	TopLeftTree.reset();
	TopRightTree.reset();
	BottomLeftTree.reset();
	BottomRightTree.reset();
}

/// <summary>
/// Inserts a given node into the quad tree
/// </summary>
/// <param name="InNode">Node to insert</param>
void QuadTree::InsertNode(Vector2 InPosition, std::shared_ptr<Actor>& InActor)
{
	//Null / boundary check
	if (!IsInBoundary(InPosition)) return;

	//Check for space
	if (abs(TopLeft.x - BottomRight.x) <= 1 && (TopLeft.y - BottomRight.y) <= 1 && IsLeaf())
	{	//Case 1, current quadrant
		//Empty node, save
		if (IsLeaf())
			AddObject(InActor);
		return;
	}

	float MidX = (TopLeft.x + BottomRight.x) / 2;
	float MidY = (TopLeft.y + BottomRight.y) / 2;

	//Figure out which tree to use
	if (MidX >= InPosition.x) // Left side
	{
		if (MidY >= InPosition.y) // Top side
		{
			//If our branch to the top left is null, make a new one
			if (TopLeftTree == nullptr)
			{
				//Top left sector
				TopLeftTree = std::make_shared<QuadTree>(
					Vector2(TopLeft.x, TopLeft.y),
					Vector2(MidX, MidY));
				//Recurse
				TopLeftTree->InsertNode(InPosition,  InActor); //TODO make reference to save memory overhead
			}
		}
		else { //Bottom side
			if (BottomLeftTree == nullptr)
			{
				//Bottom left sector
				BottomLeftTree = std::make_shared<QuadTree>(
					Vector2(TopLeft.x, MidY),
					Vector2(MidX, BottomRight.y));
				//Recurse
				BottomLeftTree->InsertNode(InPosition, InActor);
			}
		}
	}
	else //Right side
	{
		//Top side
		if (MidY >= InPosition.y)
		{
			//If our branch to the top right is null, make a new one
			if (TopRightTree == nullptr)
			{
				//Top Right sector
				TopRightTree = std::make_shared<QuadTree>(
					Vector2(MidX, TopLeft.y),
					Vector2(BottomRight.x, MidY));
				//Recurse
				TopRightTree->InsertNode(InPosition, InActor);
			}
		}
		else
		{
			//If our branch to the bottom right is null, make a new one
			if (BottomRightTree == nullptr)
			{
				//Bottom left sector
				BottomRightTree = std::make_shared<QuadTree>(
					Vector2(MidX, MidY),
					Vector2(BottomRight.x, BottomRight.y));
				//Recurse
				BottomRightTree->InsertNode(InPosition, InActor);
			}
		}
	}

}

void QuadTree::InsertNode(Vector2 InPosition)
{
}

QuadTree* QuadTree::FindNodeAtPoint(Vector2 InPoint)  
{
	// Null / boundary check
	if (!IsInBoundary(InPoint))
	{
		return nullptr;
	}

	//Return self
	if (IsLeaf()) return this;

	int MidX = int(TopLeft.x + BottomRight.x) / 2;
	int MidY = int(TopLeft.y + BottomRight.y) / 2;

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

bool QuadTree::IsInBoundary(Vector2 InPoint)
{
	return InPoint.x >= TopLeft.x && InPoint.x <= BottomRight.x && InPoint.y >= TopLeft.y && InPoint.y <= BottomRight.y;
}

#include "../Engine.h"

void QuadTreeUnitTest()
{

	//Create a tree
	std::shared_ptr<QuadTree> Root = std::make_shared<QuadTree>(Vector2(0, 0), Vector2(5, 5));
	QuadTree* ReturnValue;

	//Create world context
	World* TempWorld = new World(GET_SINGLE(EngineCore));

	//Actor
	std::shared_ptr<Actor> Actor1_1 = std::make_shared<Actor>(Vector2(1.f), TempWorld);
	std::shared_ptr<Actor> Actor4_4 = std::make_shared<Actor>(Vector2(4.f), TempWorld);

	//Insertion test
	Root->InsertNode(Actor1_1->GetActorLocation(), Actor1_1);
	Root->InsertNode(Actor4_4->GetActorLocation(), Actor4_4);
	
	//Search Test
	ReturnValue = Root->FindNodeAtPoint(Vector2(1, 1));
	ReturnValue = Root->FindNodeAtPoint(Vector2(-30, 30));
	ReturnValue = Root->FindNodeAtPoint(Vector2(4, 4));
	ReturnValue = Root->FindNodeAtPoint(Vector2(10, 14));

	bool end = true;

	delete TempWorld;

}
