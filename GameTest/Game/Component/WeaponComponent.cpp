#include "stdafx.h"
#include "WeaponComponent.h"
#include "FireControlComponent.h"
#include "../Object/Projectile.h"
#include "../../Engine/Managers/TimerManager.h"

CWeapon::CWeapon(Entity* InEntity) : CRigidBody(InEntity)
{
	SetGravityScale(0.f);
}


void CWeapon::OnBegin()
{
	//Super
	CRigidBody::OnBegin();

	if (CFireControl* FireControl = Owner->GetComponentOfClass<CFireControl>())
	{
		//Check for valid slot
		FireControl->InsertWeapon(this);
	}
}

void CWeapon::Update(float DeltaTime)
{
	CRigidBody::Update(DeltaTime);

}

Projectile* CWeapon::Fire(Vector2 FiringSolution)
{

	//OVerride old solution
	LastFiringSolution = FiringSolution;

	//Calculate launch position
	Vector2 LaunchPosition = Owner->GetEntityLocation() + Offset + FiringSolution * 40.f;

	Projectile* NewProjectile = nullptr;

	//Weapon switching //TODO move to subclasses
	switch (Type)
	{
	case EWeaponType::Cannon:

		Projectile* NewProjectile = Owner->GetWorld()->CreateEntity<Projectile>();
		NewProjectile->SetActorLocation(LaunchPosition);


		//NewProjectile->SetActorRotation(PI / 4);
		NewProjectile->ProjectileSpeed = 10.f;
		NewProjectile->Damage = 35.f;
		NewProjectile->ProjectileBody->SetVelocity(FiringSolution * 10.f);
		NewProjectile->ProjectileBody->SetGravityScale(9.8f);
		NewProjectile->Owner = Owner;
		Owner->GetWorld()->GetActiveCamera()->SetTarget(NewProjectile);


		break;

	}

	

	//Repeat
	TimerManager::GetInstance()->SetTimer(0.4f, std::bind(&CWeapon::Repeat, this), this);

	//Return
	return NewProjectile;

}

void CWeapon::Repeat()
{

	//Calculate launch position
	Vector2 LaunchPosition = Owner->GetEntityLocation() + Offset + LastFiringSolution * 40.f;

	//Weapon switching //TODO move to subclasses
	switch (Type)
	{
	case EWeaponType::Cannon:

		Projectile* NewProjectile = Owner->GetWorld()->CreateEntity<Projectile>();
		NewProjectile->SetActorLocation(LaunchPosition);


		//NewProjectile->SetActorRotation(PI / 4);
		NewProjectile->ProjectileSpeed = 10.f;
		NewProjectile->Damage = 35.f;
		NewProjectile->ProjectileBody->SetVelocity(LastFiringSolution * 10.f);
		NewProjectile->ProjectileBody->SetGravityScale(9.8f);
		NewProjectile->Owner = Owner;
		Owner->GetWorld()->GetActiveCamera()->SetTarget(NewProjectile);


		break;

	}
}