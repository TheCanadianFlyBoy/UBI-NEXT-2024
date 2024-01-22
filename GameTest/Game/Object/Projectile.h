#pragma once
/*
*	ANGRY SHIPS - Projectile
*	Basic projectile logic actor
*
*/

#include "../../Engine/Common.h"
#include "../Component/FireControlComponent.h"

class Projectile : public Actor
{
public:
	//Class Name
	inline virtual const char* GetObjectClassName() override { return GetStaticClassName(); }
	inline static const char* GetStaticClassName() { return "Projectile"; }

	Projectile(World* InWorld);

	CRigidBody* ProjectileBody;

	CSprite* SpriteComponent;

	virtual void OnBegin() override;

	virtual void Update(float DeltaTime) override;

	virtual void OnActorCollision(CollisionInfo Info) override;

	virtual void Shutdown() override;

	Entity* Owner = nullptr;

	float Damage = 50.f;
	float ProjectileSpeed = 2.f;

	EWeaponType Type = EWeaponType::Cannon;


};