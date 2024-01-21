#include "stdafx.h"
#include "Quadtree.h"
#include "../Object/Actor.h"
#include "../Component/RigidBodyComponent.h"



void QuadTree::InsertNode(Vector2 InPosition, CRigidBody* InBody)
{
	//Null / boundary check
	if (!IsInBoundary(InPosition)) return;

	//Check for space
	if (abs(TopLeft.x - BottomRight.x) <= 1 && (TopLeft.y - BottomRight.y) <= 1 && IsLeaf())
	{	//Case 1, current quadrant
		//Empty node, save
		if (IsLeaf())
			AddObject(InBody);
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
				TopLeftTree->InsertNode(InPosition, InBody); //TODO make reference to save memory overhead
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
				BottomLeftTree->InsertNode(InPosition, InBody);
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
				TopRightTree->InsertNode(InPosition, InBody);
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
				BottomRightTree->InsertNode(InPosition, InBody);
			}
		}
	}
}

void QuadTree::AddObject(CRigidBody* InBody)
{
	//Case 1: Insert into vector
	if (Bodies.size() < QUAD_MAX_CHILDREN)
	{
		Bodies.push_back(InBody);
	}
	else //Case 2: split leaf node
	{
		//Push into array
		Bodies.push_back(InBody);
		//Now split
		Split();
	}
}

void QuadTree::RemoveObject(CRigidBody* InBody)
{
	//Iterator
	std::vector<CRigidBody*>::iterator itr;

	itr = Bodies.begin();

	//Iterate
 	while (itr != Bodies.end())
	{
		//Case 1: found it
		if (*itr == InBody)
		{
			Bodies.erase(itr);
			return;
		}

		itr++;

	}

	//Case 2: check nearby branches
	if (TopLeftTree)		TopLeftTree->RemoveObject(InBody);
	if (TopRightTree)		TopLeftTree->RemoveObject(InBody);
	if (BottomLeftTree)		TopLeftTree->RemoveObject(InBody);
	if (BottomRightTree)	TopLeftTree->RemoveObject(InBody);


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
	for (auto& Child : Bodies)
	{
		//Reinsert everything
		InsertNode(Child->Position, Child);
	}

	//Clear vector
	Bodies.clear();

}

QuadTree::~QuadTree()
{
	Bodies.clear();

	TopLeftTree.reset();
	TopRightTree.reset();
	BottomLeftTree.reset();
	BottomRightTree.reset();
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

/// <summary>
/// Queries the given node from this node
/// </summary>
/// <param name="InTree"></param>
void QuadTree::Query()
{
	//Case 1: Query self
	if (!Bodies.empty())
	{
		for (auto& FirstObject : Bodies)
		{
			for (auto& SecondObject : Bodies)
			{
				//Separate, so we compare
				if (FirstObject != SecondObject)
				{
					FirstObject->GetCollision(SecondObject, CollisionInfo());
				}
			}
		}
	}

	if (!IsLeaf())
	{

	//Query Neighbours
	if (TopLeftTree)	 QueryOther(TopLeftTree.get());
	if (TopRightTree)    QueryOther(TopRightTree.get());
	if (BottomLeftTree)  QueryOther(BottomLeftTree.get());
	if (BottomRightTree) QueryOther(BottomRightTree.get());

	//Recurse
	if (TopLeftTree)	 TopLeftTree->Query();
	if (TopRightTree)    TopRightTree->Query();
	if (BottomLeftTree)  BottomLeftTree->Query();
	if (BottomRightTree) BottomRightTree->Query();

	}


}

/// <summary>
/// Check if there are any overlaps between this tree and the next
/// </summary>
/// <param name="InTree"></param>
void QuadTree::QueryOther(QuadTree* InTree)
{
	for (const auto& MyBody : Bodies)
	{
		for (const auto& TheirBody : InTree->Bodies)
		{
			MyBody->GetCollision(TheirBody, CollisionInfo());
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
	//std::shared_ptr<QuadTree> Root = std::make_shared<QuadTree>(Vector2(0, 0), Vector2(5, 5));
	//QuadTree* ReturnValue;
	//
	////Create world context
	////World* TempWorld = new World(GET_SINGLE(EngineCore));
	//
	////Actor
	////std::shared_ptr<Actor> Actor1_1 = std::make_shared<Actor>(Vector2(1.f), TempWorld);
	////std::shared_ptr<Actor> Actor4_4 = std::make_shared<Actor>(Vector2(4.f), TempWorld);
	//
	////Insertion test
	////Root->InsertNode(Actor1_1->GetActorLocation(), Actor1_1);
	////Root->InsertNode(Actor4_4->GetActorLocation(), Actor4_4);
	//
	////Search Test
	//ReturnValue = Root->FindNodeAtPoint(Vector2(1, 1));
	//ReturnValue = Root->FindNodeAtPoint(Vector2(-30, 30));
	//ReturnValue = Root->FindNodeAtPoint(Vector2(4, 4));
	//ReturnValue = Root->FindNodeAtPoint(Vector2(10, 14));
	//
	//bool end = true;
	//
	//delete TempWorld;

}
