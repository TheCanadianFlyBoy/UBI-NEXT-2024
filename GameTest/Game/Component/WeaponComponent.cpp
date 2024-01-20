#include "stdafx.h"
#include "WeaponComponent.h"
#include "FireControlComponent.h"
#include "../Object/Projectile.h"

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

void CWeapon::Fire(Vector2 FiringSolution)
{

	//Calculate launch position
	Vector2 LaunchPosition = Owner->GetEntityLocation() + Offset + FiringSolution * 40.f;

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
	

}