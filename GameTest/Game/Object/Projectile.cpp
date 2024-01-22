#include "stdafx.h"
#include "Projectile.h"
#include "../Component/FireControlComponent.h"

/// <summary>
/// Creates the rigid body necessary for the projectile
/// </summary>
/// <param name="InWorld"></param>
Projectile::Projectile(World* InWorld) : Actor(InWorld)
{
	ProjectileBody = CreateComponent<CRigidBody>();
	ProjectileBody->SetMass(1.f);
	ProjectileBody->SetGravityScale(1.f);
	ProjectileBody->SetDensity(3000.f);
	ProjectileBody->MakeCollisionCircle(Vector2(0.f), 4.f);
	ProjectileBody->SetupBuoyancyCircles();

	AutoDeactivates = true;

	SetLifetimeMax(10.f);

}

void Projectile::OnBegin()
{
	Actor::OnBegin();

	//Set class defaults
	ProjectileBody->SetVelocity(Vector2(0.f));


}

/// <summary>
/// Handle the additonal projectiles types
/// </summary>
/// <param name="DeltaTime"></param>
void Projectile::Update(float DeltaTime)
{
	Actor::Update(DeltaTime);

	switch (Type)
	{
	case EWeaponType::Rocket:
	{
		Vector2 Velocity = ProjectileBody->GetVelocity();
		Velocity *= 1.07f;
		Velocity += (ENGINE->FRandRange(-0.2f, 0.2f));
		ProjectileBody->SetVelocity(Velocity);
		break;
	}
	}

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

		//Additional nullguard
		if (!HealthComponent) return;

		//Calculate positional damage
		float DistanceToCentreOfMass = (HealthComponent->Owner->GetEntityLocation().DistanceFrom(Info.ImpactPoint));
		float PositionalDamage = Damage * (std::max<float>(1.f - (1.f / 1000.f * sqrtf(DistanceToCentreOfMass)), 0.f)); //TODO make variable based on projectile type //TODO UNSAFE SQRT
		

		//Take damage
		HealthComponent->TakeDamage(PositionalDamage);

		Debug::DrawCircle(Vector2(500.f), 40, 4, Color3(1.f, 0.f, 0.f));

		if (!HealthComponent->Alive())
		{
			Info.OtherActor->Shutdown();
		}

		//Self deletion
		Shutdown();

		//Spawn particle
		ParticleSprite* Particle = Owner->GetWorld()->CreateEntity<ParticleSprite>();
		Particle->SetActorLocation(GetEntityLocation());
		Particle->SpriteComponent->SetSprite("Explosion1");
		Particle->SpriteComponent->SetAnimation(0, true);
		Particle->SetLifetime(1.f);

		//SetActorLocation(Vector2(0.f));

	}
}

/// <summary>
/// Shut down
/// </summary>
void Projectile::Shutdown()
{
	

	Actor::Shutdown();
}
