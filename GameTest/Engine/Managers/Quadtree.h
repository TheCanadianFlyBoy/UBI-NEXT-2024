#pragma once
/*
*	CFB Engine - Quad Tree
*	Handles spatial partitioning
*
*/

#include <memory>
#include "../Math/Vector2.h"

#define QUAD_MAX_CHILDREN 8

class Actor;

class QuadTree {
public://Common
	QuadTree(Vector2 TopLeftPoint = Vector2(0.f), Vector2 BottomRightPoint = Vector2(0.f)) : TopLeft(TopLeftPoint), BottomRight(BottomRightPoint) {
		//Objects.reserve(QUAD_MAX_CHILDREN);
	};

	~QuadTree();

	//Unit test data
	//int Data;

	//Points to child or first element
	std::vector<std::shared_ptr<Actor>> Objects;

	//Return if this is a leaf
	inline bool IsLeaf() { return !TopLeftTree && !TopRightTree && !BottomLeftTree && !BottomRightTree; }

	//Insertion
	void InsertNode(Vector2 InPosition, std::shared_ptr<Actor>& InActor);

	//Add object or call c
	void AddObject(std::shared_ptr<Actor> InActor);

	void Split();

protected: //Members
	//Boundaries
	Vector2 TopLeft = Vector2(0.f);
	Vector2 BottomRight = Vector2(0.f);

	//Pointer to data
	//std::shared_ptr<QuadNode> Node = nullptr;

	//Pointer to links
	std::shared_ptr<QuadTree> TopLeftTree = nullptr;
	std::shared_ptr<QuadTree> TopRightTree = nullptr;
	std::shared_ptr<QuadTree> BottomLeftTree = nullptr;
	std::shared_ptr<QuadTree> BottomRightTree = nullptr;


public: // Methods

	//Insert a node in the tree system
	void InsertNode(Vector2 InPosition);

	//Find a node
	QuadTree* FindNodeAtPoint(Vector2 InPoint);

	//Check if within our quad
	bool IsInBoundary(Vector2 InPoint);


};

void QuadTreeUnitTest();