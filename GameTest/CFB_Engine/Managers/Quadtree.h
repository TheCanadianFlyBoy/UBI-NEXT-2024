#pragma once
/*
*	CFB Engine - Quad Tree
*	Handles spatial partitioning
*
*/

#include <memory>

struct QuadPoint {
	int x;
	int y;

	QuadPoint(int inX = 0, int inY = 0) : x(inX), y(inY) {};

};

struct QuadNode {
	QuadPoint Position;
	//Points to child or first element
	int Data;
	//Number of elements or -1 if not a leaf
	//int Count;

	QuadNode(QuadPoint InPosition, int InData = 0) : Position(InPosition), Data(InData) {};



};


class QuadBranch {
public://Common
	QuadBranch(QuadPoint TopLeftPoint = QuadPoint(), QuadPoint BottomRightPoint = QuadPoint()) {}

	int MaxLeaves = 8;

protected: //Members
	//Boundaries
	QuadPoint TopLeft = QuadPoint(0,0);
	QuadPoint BottomRight = QuadPoint(0, 0);

	//Pointer to data
	std::shared_ptr<QuadNode> Node = nullptr;

	//Pointer to links
	std::shared_ptr<QuadBranch> TopLeftTree = nullptr;
	std::shared_ptr<QuadBranch> TopRightTree = nullptr;
	std::shared_ptr<QuadBranch> BottomLeftTree = nullptr;
	std::shared_ptr<QuadBranch> BottomRightTree = nullptr;

public: // Methods

	//Insert a node in the tree system
	void InsertNode(std::shared_ptr<QuadNode> InNode);

	//Find a node
	std::shared_ptr<QuadNode> FindNodeAtPoint(QuadPoint InPoint);

	//Check if within our quad
	bool IsInBoundary(QuadPoint InPoint);


};
