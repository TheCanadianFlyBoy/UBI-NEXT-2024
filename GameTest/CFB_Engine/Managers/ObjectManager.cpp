#include "stdafx.h"
#include "ObjectManager.h"

//Delete all the objects
ObjectManager::~ObjectManager()
{
	//Clear all the vector
	for (auto &VectorPair : Entities)
	{
		//Get the vector value
		VectorPair.second.clear();
	}
}
