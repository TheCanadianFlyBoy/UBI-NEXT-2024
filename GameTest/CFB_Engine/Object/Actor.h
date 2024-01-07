#pragma once
/*
*	CFB Engine - Actor
*	A common entity type that has a transform by default
*
*/

#include "Entity.h"
#include "../Component/TransformComponent.h"

class Actor : public Entity
{
public:
	//Class Name
	inline virtual const char* GetObjectClassName() override { return GetStaticClassName(); }
	inline static const char* GetStaticClassName() { return "Actor"; }

	Actor(ObjectManager* InWorld = nullptr) : Entity(InWorld) { CreateComponent<CTransform>(); }

};