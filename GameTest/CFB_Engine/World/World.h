#pragma once
/*
*	CFB Engine - World
*	The archetype for all worlds in the game, containing managers and objects.
*
*/

#include "../Object/Object.h"
#include <memory>

class ObjectManager;

class World : public Object
{
public:
	//Class Name
	inline virtual const char* GetObjectClassName() override { return GetStaticClassName(); }
	inline static const char* GetStaticClassName() { return "World"; }

	//Constructor
	World();

	//Update
	virtual void Update(float DeltaTime);
	virtual void Draw(); //TODO camera

protected:

	//Object Manager
	std::unique_ptr<ObjectManager> pObjectManager;


};