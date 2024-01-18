#pragma once
/*
*	CFB Engine - Rigid Body Component
*	The archetype for all collision components in within the engine.
*
*/

#include <memory>

#include "Component.h"
#include "TransformComponent.h"
#include "../Math/Vector2.h"

class Entity;

struct CollisionBox; struct CollisionCircle; struct CollisionLine; struct CollisionInfo; struct CollisionPrimitive;



class CRigidBody : public CTransform
{
public: //Properties
	//Class Name
	inline virtual const char* GetObjectClassName() override { return GetStaticClassName(); }
	inline static const char* GetStaticClassName() { return "CRigidBody"; }

	//Constructor with optional args
	CRigidBody(Entity* InEntity = nullptr) : CTransform(InEntity) {};

	//Update
	virtual void Update(float DeltaTime);

public: //Factory

	//Collision Makers
	void MakeCollisionCircle(Vector2 InPosition, float InRadius);
	void MakeCollisionBox(Vector2 InPosition, Vector2 InDimensions);

	inline CollisionPrimitive* GetCollisionShape() { return CollisionShape.get(); }
	//Gets if there is a collision between two bodies
	virtual bool GetBodyCollision(CRigidBody* Other, CollisionInfo& OutHitInfo); 

	//Static check for checking two collisions TODO
	//inline static bool CheckCollision(CRigidBody* This, CRigidBody* Other) { This->GetBodyCollision(Other); }

protected: // Methods


protected: // Members

	std::unique_ptr<CollisionPrimitive> CollisionShape = nullptr;
	
	

};