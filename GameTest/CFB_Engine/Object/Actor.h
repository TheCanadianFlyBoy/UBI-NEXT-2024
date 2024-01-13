#pragma once
/*
*	CFB Engine - Actor
*	A common entity type that has a transform by default
*
*/

#include "Entity.h"
#include "../Component/TransformComponent.h"
#include "../World/World.h"

class Actor : public Entity
{
public:
	//Class Name
	inline virtual const char* GetObjectClassName() override { return GetStaticClassName(); }
	inline static const char* GetStaticClassName() { return "Actor"; }

	Actor(World* InWorld = nullptr) : Entity(InWorld) { Transform = CreateComponent<CTransform>(); }

public: //Helper Methods
	//Setters
	inline void SetActorLocation(Vector2 InVector) { Transform->SetPosition(InVector); };
	inline void SetActorRotation(float InRotation) { Transform->SetRotation(InRotation); };

	//Getters
	inline Vector2 GetActorLocation() { return Transform->GetPosition(); };
	inline float GetActorRotation() { return Transform->GetRotation(); };

	//Adders
	inline void AddActorLocation(Vector2 InVector) { Transform->AddPosition(InVector); }
	inline void AddActorRotation(float InRotation) { Transform->AddRotation(InRotation); };

protected: //Members
	//Transform reference for easy reference/usage within the class
	CTransform* Transform = nullptr;
};