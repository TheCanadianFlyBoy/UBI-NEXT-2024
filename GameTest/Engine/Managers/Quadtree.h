#pragma once
/*
*	 Engine - Quad Tree
*	Handles spatial partitioning
*
*/

#include <memory>
#include "../Math/Vector2.h"

#define QUAD_MAX_CHILDREN 120

class Actor; class CRigidBody;

class QuadTree {
public://Common
	QuadTree(Vector2 TopLeftPoint = Vector2(0.f), Vector2 BottomRightPoint = Vector2(0.f)) : TopLeft(TopLeftPoint), BottomRight(BottomRightPoint) {
		//Objects.reserve(QUAD_MAX_CHILDREN);
	};

	~QuadTree();

	//Unit test data
	//int Data;

	

	//Return if this is a leaf
	inline bool IsLeaf() { return !TopLeftTree && !TopRightTree && !BottomLeftTree && !BottomRightTree; }

	//Insertion
	void InsertNode(Vector2 InPosition, CRigidBody* InBody);

	//Add object or call c
	void AddObject(CRigidBody* InBody);

	void RemoveObject(CRigidBody* InBody);

	//Split a leaf node
	void Split();

	//Clear the entire tree
	inline void ClearTree() { 
		Bodies.clear(); 
		if (TopLeftTree)		TopLeftTree->ClearTree();
		if (TopRightTree)		TopRightTree->ClearTree();
		if (BottomLeftTree)		BottomLeftTree->ClearTree();
		if (BottomRightTree)	BottomRightTree->ClearTree();
	}

	//Points to child or first element
	std::vector<CRigidBody*> Bodies;

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


	//Find a node
	QuadTree* FindNodeAtPoint(Vector2 InPoint);


	//Shorthand for self query at root
	inline void StartQuery() { Query(); }

	//Queries the tree for collisions
	void Query();

	void QueryOther(QuadTree* InTree);



	//Check if within our quad
	bool IsInBoundary(Vector2 InPoint);


};

void QuadTreeUnitTest();