#include "stdafx.h"
#include "Projectile.h"

/// <summary>
/// Creates the rigid body necessary for the projectile
/// </summary>
/// <param name="InWorld"></param>
Projectile::Projectile(World* InWorld) : Actor(InWorld)
{
	ProjectileBody = CreateComponent<CRigidBody>();
	OnBegin();
}

void Projectile::OnBegin()
{
	Actor::OnBegin();

	//Set class defaults
	
	ProjectileBody->MakeCollisionCircle(Vector2(0.f), 15.f);
	ProjectileBody->SetVelocity(Vector2(0.f));
	ProjectileBody->SetMass(1.f);
	ProjectileBody->SetGravityScale(1.f);
}

void Projectile::OnActorCollision(CollisionInfo Info)
{
	if (Info.ThisActor && Info.OtherActor && (Info.OtherActor != Owner && Info.ThisActor != Owner))
	{
		//Check health
		if (CHealth* HealthComponent = Info.OtherActor->GetComponentOfClass<CHealth>())
		{
			//Take damage
			HealthComponent->TakeDamage(Damage);

			Debug::DrawCircle(Vector2(500.f), 40, 4, Color3(1.f, 0.f, 0.f));

			if (!HealthComponent->Alive())
			{
				Info.OtherActor->Shutdown();
			}

		}
		//Check health
		if (CHealth* HealthComponent = Info.ThisActor->GetComponentOfClass<CHealth>())
		{
			//Take damage
			HealthComponent->TakeDamage(Damage);

			Debug::DrawCircle(Vector2(500.f), 40, 4, Color3(1.f, 0.f, 0.f));

			if (!HealthComponent->Alive())
			{
				Info.OtherActor->Shutdown();
			}

		}
	}
}
