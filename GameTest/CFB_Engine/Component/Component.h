#pragma once
/*
*	CFB Engine - Component
*	The archetype for all components in within the ECS.
*
*/

#include "../Object/Object.h"
#include <string>

class Entity;

class Component : public Object
{
public:

	//Constructor with optional ownership
	Component(Entity* InOwner = nullptr) : Owner(InOwner) {};

	//Owner
	Entity* Owner = nullptr;
	


};