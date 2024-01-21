#include "stdafx.h"
#include "WeaponComponent.h"
#include "FireControlComponent.h"
#include "../Object/Projectile.h"
#include "../../Engine/Engine.h"
#include "../../Engine/Managers/TimerManager.h"

CWeapon::CWeapon(Entity* InEntity) : CTransform(InEntity)
{
}


void CWeapon::OnBegin()
{
	//Super
	CTransform::OnBegin();

	if (CFireControl* FireControl = Owner->GetComponentOfClass<CFireControl>())
	{
		//Check for valid slot
		FireControl->InsertWeapon(this);
	}
}

void CWeapon::Update(float DeltaTime)
{
	CTransform::Update(DeltaTime);

}

Projectile* CWeapon::Fire(Vector2 FiringSolution)
{

	//OVerride old solution
	LastFiringSolution = FiringSolution;

	//Calculate launch position
	Vector2 LaunchPosition = Owner->GetEntityLocation() + Position + FiringSolution * 40.f;

	Projectile* NewProjectile = nullptr;

	//Weapon switching //TODO move to subclasses
	switch (Type)
	{
	case EWeaponType::Cannon:

		NewProjectile = Owner->GetWorld()->CreateEntity<Projectile>();
		NewProjectile->SetActorLocation(LaunchPosition);


		//NewProjectile->SetActorRotation(PI / 4);
		NewProjectile->ProjectileSpeed = ProjectileSpeed;
		NewProjectile->Damage = ProjectileDamage;
		NewProjectile->ProjectileBody->SetVelocity(FiringSolution * 10.f);
		NewProjectile->ProjectileBody->SetGravityScale(9.8f);
		NewProjectile->ProjectileBody->SetMass(ProjectileMass);
		NewProjectile->Owner = Owner;
		Owner->GetWorld()->GetActiveCamera()->SetTarget(NewProjectile);


		break;

	}

	

	CurrentProjectileBurst++;
	//Repeat
	if (CurrentProjectileBurst < ProjectileCount)
	{
		TimerManager::GetInstance()->SetTimer(0.4f, std::bind(&CWeapon::Repeat, this), this);
	}
	else 
	{
		CurrentProjectileBurst = 0;
	}
	//Return
	return NewProjectile;

}

void CWeapon::Repeat()
{
	Vector2 Wobble = Vector2(
		ENGINE->RandRangeF(-AimWobble, AimWobble),
		ENGINE->RandRangeF(-AimWobble, AimWobble));

	LastFiringSolution = (LastFiringSolution + Wobble);

	Fire(LastFiringSolution);
}