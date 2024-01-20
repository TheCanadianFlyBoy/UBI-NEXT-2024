#pragma once
/*
*	CFB Engine - Object
*	The archetype for all objects within the ECS.
*
*/

#include <vector>
#include <string>
#include <memory>

//Forward declaration
class Component; class CCamera;

class Object
{
	friend class ObjectManager;
public: //Common
	//Constructor
	Object() { };

	// Class Name
	inline virtual const char* GetObjectClassName() = 0;

	//Instance Name
	inline std::string GetInstanceName() { return InstanceName; }
	inline void SetInstanceName(std::string InName) { InstanceName = InName; }

public: //Methods
	//Gameloop
	//On initial game start
	virtual void OnBegin();
	//Frame start
	virtual void Update(float DeltaTime) {};
	//Frame end
	virtual void LateUpdate(float DeltaTime);
	//Draw call
	virtual void Render(CCamera* InCamera = nullptr) {};
	//On deletion / world end
	virtual void Shutdown() { Active = false; };

	//Deactivate

public: // Members
	//Active flag
	bool Active = true;
	bool AutoDeactivates = false;

protected: // Members
	//Name
	std::string InstanceName;
	//Current lifetime
	float LifetimeMax = -1.f;
	float CurrentLifetime = 0.f;

};