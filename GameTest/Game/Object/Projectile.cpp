#include "stdafx.h"
#include "Projectile.h"

/// <summary>
/// Creates the rigid body necessary for the projectile
/// </summary>
/// <param name="InWorld"></param>
Projectile::Projectile(World* InWorld) : Actor(InWorld)
{
	ProjectileBody = CreateComponent<CRigidBody>();
	ProjectileBody->SetMass(1.f);
	ProjectileBody->SetGravityScale(1.f);
	ProjectileBody->MakeCollisionCircle(Vector2(0.f), 4.f);
}

void Projectile::OnBegin()
{
	Actor::OnBegin();

	//Set class defaults
	ProjectileBody->SetVelocity(Vector2(0.f));


}

Vector2 Hit1 = Vector2(-1.f);
Vector2 Hit2 = Vector2(-1.f);

void Projectile::OnActorCollision(CollisionInfo Info)
{
	if (Info.ThisActor && Info.OtherActor && Info.OtherActor != Owner && Info.ThisActor != Owner)
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

		} else if (CHealth* HealthComponent = Info.ThisActor->GetComponentOfClass<CHealth>())
		{
			//Take damage
			HealthComponent->TakeDamage(Damage);

			Debug::DrawCircle(Vector2(500.f), 40, 4, Color3(1.f, 0.f, 0.f));

			if (!HealthComponent->Alive())
			{
				Info.OtherActor->Shutdown();
			}

		}

		//Self deletion
		Shutdown();

		//SetActorLocation(Vector2(0.f));

	}
}

/// <summary>
/// Shut down
/// </summary>
void Projectile::Shutdown()
{
	//Spawn particle
	ParticleSprite* Particle = Owner->GetWorld()->CreateEntity<ParticleSprite>();
	Particle->SetActorLocation(GetEntityLocation());
	Particle->SpriteComponent->SetSprite("Explosion1");
	Particle->SpriteComponent->SetAnimation(0, true);
	Particle->SetLifetime(1.f);

	Actor::Shutdown();
}
