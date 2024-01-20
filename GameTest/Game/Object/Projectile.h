#pragma once
/*
*	ANGRY SHIPS - Projectile
*	Basic projectile logic actor
*
*/

#include "../../Engine/Common.h"
#include "HealthComponent.h"


class Projectile : public Actor
{
public:
	Projectile(World* InWorld);

	CRigidBody* ProjectileBody;

	virtual void OnActorCollision(CollisionInfo Info) override {
		if (Info.OtherActor && Info.OtherActor)
		{
			//Check health
			if (CHealth* HealthComponent = Info.OtherActor->GetComponentOfClass<CHealth>())
			{
				//Take damage
				HealthComponent->TakeDamage(Damage);
			}
		}
	}

	Entity* Owner = nullptr;

	float Damage = 50.f;
	float ProjectileSpeed = 2.f;

};