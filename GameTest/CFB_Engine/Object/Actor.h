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

	Actor(World* InWorld = nullptr) : Entity(InWorld) { Transform = CreateComponent<CTransform>(); }

public: //Helper Methods
	inline void SetActorLocation(Vector2 InVector) { Transform->SetPosition(InVector); };
	inline void SetActorRotation(float InRotation) { Transform->SetRotation(InRotation); };

protected: //Members
	//Transform reference for easy reference/usage within the class
	CTransform* Transform = nullptr;
};