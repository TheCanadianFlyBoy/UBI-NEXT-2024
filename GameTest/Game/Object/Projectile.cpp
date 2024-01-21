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

		CHealth* HealthComponent;

		//Check health
		HealthComponent = Info.OtherActor->GetComponentOfClass<CHealth>();
		if (!HealthComponent) //Swap in case of reversed collision event
			HealthComponent = Info.ThisActor->GetComponentOfClass<CHealth>();

		//Calculate positional damage
		float DistanceToCentreOfMass = (HealthComponent->Owner->GetEntityLocation().DistanceFrom(Info.ImpactPoint));
		float PositionalDamage = Damage * (std::max<float>(1.f - (1.f / 10.f * sqrtf(DistanceToCentreOfMass)), 0.f)); //TODO make variable based on projectile type
		

		//Take damage
		HealthComponent->TakeDamage(PositionalDamage);

		Debug::DrawCircle(Vector2(500.f), 40, 4, Color3(1.f, 0.f, 0.f));

		if (!HealthComponent->Alive())
		{
			Info.OtherActor->Shutdown();
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
