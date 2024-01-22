#pragma once
/*
*	 Engine - Actor
*	A common entity type that has a transform by default
*
*/

#include "Entity.h"
#include "../Component/TransformComponent.h"
#include "../World/World.h"

class Actor : public Entity
{
	friend class GameState; friend class Controller;
public:
	//Class Name
	inline virtual const char* GetObjectClassName() override { return GetStaticClassName(); }
	inline static const char* GetStaticClassName() { return "Actor"; }

	Actor(World* InWorld = nullptr) : Entity(InWorld) { Transform = CreateComponent<CTransform>(); }
	//Actor(Vector2 Position, World* InWorld = nullptr) : Entity(InWorld) { Transform = CreateComponent<CTransform>(); Transform->SetPosition(Position); }

	//virtual void OnBegin() override {  }

	virtual ~Actor() {};

public: //Helper Methods
	//Setters
	inline void SetActorLocation(Vector2 InVector) { Transform->SetPosition(InVector); };
	inline void SetActorLocation(Entity* InEntity) { if (InEntity) Transform->SetPosition(InEntity->GetEntityLocation()); }
	inline void SetActorRotation(float InRotation) { Transform->SetRotation(InRotation); };

	//Getters
	inline Vector2 GetActorLocation() { return Transform->GetPosition(); };
	inline float GetActorRotation() { return Transform->GetRotation(); };

	//Adders
	inline void AddActorLocation(Vector2 InVector) { Transform->AddPosition(InVector); }
	inline void AddActorRotation(float InRotation) { Transform->AddRotation(InRotation); };

	virtual void OnActorCollision(CollisionInfo InInfo) { };

	inline Controller* GetController() { return ThisController; }

protected: //Members
	//Transform reference for easy reference/usage within the class
	CTransform* Transform = nullptr;

	//Controller Pointer
	Controller* ThisController = nullptr;

	inline void NotifyCollision(CollisionInfo InInfo) { OnActorCollision(InInfo); }

};