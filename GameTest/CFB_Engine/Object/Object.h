#pragma once
/*
*	CFB Engine - Object
*	The archetype for all objects within the ECS.
*
*/

#include <vector>
#include <memory>

//Forward declaration
class Component;

class Object
{
public:
	//Constructor
	Object() {};

	// Class Name
	inline virtual const char* GetObjectClassName() = 0;

	//Active flag
	bool Active = true;

};