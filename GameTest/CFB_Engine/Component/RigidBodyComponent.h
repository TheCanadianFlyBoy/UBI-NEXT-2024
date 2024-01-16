#pragma once
/*
*	CFB Engine - Rigid Body Component
*	The archetype for all collision components in within the engine.
*
*/

#include "Component.h"
#include "../Math/Vector2.h"

class Entity;

/// <summary>
/// A struct containing all the relevant info of a collision
/// </summary>
struct CollisionInfo
{
	//This
	Entity* This;
	CRigidBody* ThisBody;

	//Other
	Entity* Other;
	CRigidBody* OtherBody;

	//Impact info
	Vector2 ImpactPoint;
	Vector2 Normal;


};

struct AABB
{
	//Properties
	Vector2 Position = Vector2(0.f);
	Vector2 Bounds = Vector2(0.f);
	bool PositionCentred = false;
		//Methods
	//Getters
	inline Vector2 GetMin() const {
		return Vector2(
			PositionCentred ? Position.x - (Bounds.x / 2) : Position.x,
			PositionCentred ? Position.y - (Bounds.y / 2) : Position.y
		);
	};
	inline Vector2 GetMax() const {
		return Vector2(
			PositionCentred ? Position.x + (Bounds.x / 2) : Position.x,
			PositionCentred ? Position.y + (Bounds.y / 2) : Position.y
		);
	};

	//Checkers
	inline bool PointToAABB(Vector2& Point) const {
		//Get mins and maxes	
		Vector2 Min = GetMin();
		Vector2 Max = GetMax();
		//Return result of check
		return (Point.x >= Min.x && Point.x <= Max.x && Point.y >= Min.y && Point.y <= Max.y);

	};
	inline bool AABBtoAABB(AABB& Other) const {
		//Get mins and maxes
		Vector2 ThisMin = GetMin();
		Vector2 ThisMax = GetMax();
		Vector2 OtherMin = Other.GetMin();
		Vector2 OtherMax = Other.GetMax();

		return (ThisMin.x >= OtherMin.x && ThisMax.x <= OtherMax.x && 
			ThisMin.y >= OtherMin.y && ThisMax.y <= OtherMax.y);

	}


};

class CRigidBody : public Component
{
public: //Properties
	//Class Name
	inline virtual const char* GetObjectClassName() override { return GetStaticClassName(); }
	inline static const char* GetStaticClassName() { return "CRigidBody"; }

	//Constructor with optional args
	CRigidBody(Entity* InEntity = nullptr) : Component(InEntity) {};

	//Static check for checking two collisions TODO
	//inline static bool CheckCollision(CRigidBody* This, CRigidBody* Other) { This->GetBodyCollision(Other); }

protected: // Methods

	//Gets if there is a collision between two bodies
	virtual bool GetBodyCollision(CRigidBody* Other, CollisionInfo& OutHitInfo) = 0;

	

};