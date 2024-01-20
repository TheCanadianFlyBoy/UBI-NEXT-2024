#pragma once
/*
*	CFB Engine - Easing Component
*	A simple but portable component to ease an actor to a target
*
*/

#include "Component.h"
//#include "../Object/Actor.h"

//class CEasing : public Component 
//{
//public:
//	//Class Name
//	inline virtual const char* GetObjectClassName() override { return GetStaticClassName(); }
//	inline static const char* GetStaticClassName() { return "CRigidBody"; }
//
//	//Constructor
//	CEasing(Entity* InEntity) : Component(InEntity) { ActorOwner = dynamic_cast<Actor*>(InEntity); };
//
//
//	virtual void Update(float DeltaTime) override {
//		//If invalid targets, return
//		if (!ActorOwner || !Target) return;
//		//Lerp
//		Vector2 Position = MathOps::VectorLerp(ActorOwner->GetActorLocation(), Target->GetActorLocation(), DeltaTime);
//		//Set
//		ActorOwner->SetActorLocation(Position);
//	}
//
//
//
//protected:
//
//	Actor* ActorOwner = nullptr;
//	Actor* Target = nullptr;
//
//
//
//};