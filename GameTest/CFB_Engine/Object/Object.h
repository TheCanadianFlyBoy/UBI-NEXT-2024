#pragma once
/*
*	CFB Engine - Object
*	The archetype for all objects within the ECS.
*
*/

#include <vector>
#include <memory>

//Forward declaration
class Component; class CCamera;

class Object
{
public:
	//Constructor
	Object() {};

	// Class Name
	inline virtual const char* GetObjectClassName() = 0;
	
	//Common Methods
	virtual void OnBegin() {};
	virtual void Update(float DeltaTime) {};
	virtual void LateUpdate(float DeltaTime) {};
	virtual void Shutdown() {};
	virtual void Render(CCamera* InCamera = nullptr) {};

	//Active flag
	bool Active = true;

};