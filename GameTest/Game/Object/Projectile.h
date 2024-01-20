#pragma once
/*
*	ANGRY SHIPS - Projectile
*	Basic projectile logic actor
*
*/

#include "../../Engine/Common.h"


class Projectile : public Actor
{
public:
	//Class Name
	inline virtual const char* GetObjectClassName() override { return GetStaticClassName(); }
	inline static const char* GetStaticClassName() { return "Projectile"; }

	Projectile(World* InWorld);

	CRigidBody* ProjectileBody;

	virtual void OnBegin() override;

	virtual void OnActorCollision(CollisionInfo Info) override;

	virtual void Shutdown() override;

	Entity* Owner = nullptr;

	float Damage = 50.f;
	float ProjectileSpeed = 2.f;

};