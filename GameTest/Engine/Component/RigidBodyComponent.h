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

struct BuoyancyCircle : public CTransform
{
	BuoyancyCircle(Entity* InEntity, Vector2 InOffset, float InRadius, float InAdjustment) : CTransform(InEntity, InOffset), Radius(InRadius), Adjustment(InAdjustment) {}

	float Radius;
	float Adjustment;

};

class CRigidBody : public CTransform
{
public: //Properties
	//Class Name
	inline virtual const char* GetObjectClassName() override { return GetStaticClassName(); }
	inline static const char* GetStaticClassName() { return "CRigidBody"; }

	//Constructor with optional args
	CRigidBody(Entity* InEntity = nullptr);
	~CRigidBody();

	//Update
	virtual void OnBegin() override;
	virtual void Update(float DeltaTime) override;
	virtual void LateUpdate(float DeltaTime) override;
	virtual void Render(CCamera* InCamera) override;
	virtual void Shutdown() override;

public: //Collision

	//Collision Makers
	void MakeCollisionCircle(Vector2 InPosition, float InRadius);
	inline void MakeCollisionCircle(float InRadius) { MakeCollisionCircle(Vector2(0.f), InRadius); }

	void MakeCollisionBox(Vector2 InPosition, Vector2 InDimensions);
	inline void MakeCollisionBox(Vector2 InDimensions) { MakeCollisionBox(Vector2(0.f), InDimensions); }

	inline CollisionPrimitive* GetCollisionShape() { return CollisionShape.get(); }
	//Gets if there is a collision between two bodies
	virtual bool GetCollision(CRigidBody* Other, CollisionInfo& OutHitInfo); 
	//Raw collision with primitive
	virtual bool GetCollision(CollisionPrimitive& InCollisionPrimitive, CollisionInfo& OutHitInfo);

	inline void AddIgnoredEntity(Entity* Other) { IgnoredEntities.push_back(Other); }

	//Debouncing for overlaps
	void RegisterOverlappingBody(CRigidBody* InBody);
	void RemoveOverlappingBody(CRigidBody* InBody);
	bool IsOverlappingBody(CRigidBody* InBody);

public: // Methods

	//Offset
	inline void SetOffset(Vector2 InOffset) { Offset = InOffset; }
	inline Vector2 GetOffset() { return Offset; }
	//Static check for checking two collisions TODO
	
	//Mass
	inline void SetMass(float InMass) { Mass = InMass; }
	inline float GetMass() { return Mass; }

	//Velocity
	inline void SetVelocity(Vector2& InVector) { Velocity = InVector; }
	inline Vector2 GetVelocity() { return Velocity; };

	//Gravity
	inline float GetGravityScale() { return GravityScale; }
	inline void SetGravityScale(float InGravity) { GravityScale = InGravity; }

	//Buoyancy
	virtual void SetupBuoyancyCircles();
	virtual void ApplyBuoyancy(float DeltaTime);
	inline void SetBuoyancyCircleRadius(float InRadius) { BuoyancyCircleRadius = InRadius; }
	inline float GetBuoyancyCircleRadius() { return BuoyancyCircleRadius; };
	//Physics Damping
	virtual void Damping(float DeltaTime);


protected: // Methods

	//Calculate 
	void SetupBoxBuoyancy();


protected: // Members
	//Offset
	Vector2 Offset = Vector2(0.f);

	//Velocity
	Vector2 Velocity = Vector2(0.f);
	float VelocityDamping = 1.f;
	//Angular Velocity
	float AngularVelocity = 0.f;
	float AngularDamping = 0.1f;
	//Gravity
	float GravityScale = 1.f;
	float Mass = 1.f;
	float ObjectDensity = 1.f;
	//Buoyancy
	float WaterLevel = 224.f;
	float BuoyancyCircleRadius = 12;
	std::vector<std::shared_ptr<BuoyancyCircle>> BuoyancyCircles;
	//Collision
	std::unique_ptr<CollisionPrimitive> CollisionShape = nullptr;
	std::vector<CRigidBody*> OverlappingBodies;
	std::vector<Entity*> IgnoredEntities;
	
	

};