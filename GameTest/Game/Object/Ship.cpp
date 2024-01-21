#include "stdafx.h"
#include "../../Engine/Common.h"
#include "Ship.h"

#include "../Component/FireControlComponent.h"

/// <summary>
/// Default constructor
/// </summary>
/// <param name="InWorld"></param>
Ship::Ship(World* InWorld) : Actor(InWorld)
{
	//Construct components
	
	//Create sprite
	SpriteComponent = CreateComponent<CSprite>();

	//Create rigid body
	RigidBodyComponent = CreateComponent<CRigidBody>();

	//Create fire control
	FireControlComponent = CreateComponent<CFireControl>();

	HealthComponent = CreateComponent<CHealth>();

}

//Toggles the fire control system
void Ship::Possess()
{
	FireControlComponent->Active = true;
}

void Ship::UnPossess()
{
	FireControlComponent->Active = false;
}


/// <summary>
/// Default constructor for destroyer.
/// Complement:
/// 1x Main Gun
/// </summary>
/// <param name="InWorld"></param>
Destroyer::Destroyer(World* InWorld) : Ship(InWorld)
{
	
	SpriteComponent->SetSprite("Destroyer");
	SpriteComponent->SetPosition(Vector2(5, 16.f));

	Vector2 HullDimensions = SpriteManager::GetInstance()->GetSpriteDimensions("DestroyerHull");
	RigidBodyComponent->MakeCollisionBox(
		GetActorLocation(), HullDimensions - Vector2(0.f, HullDimensions.y / 2)
	);

	RigidBodyComponent->MakeCollisionBox(GetActorLocation(), HullDimensions - Vector2(0.f, HullDimensions.y / 2));
	RigidBodyComponent->SetBuoyancyCircleRadius(8);
	RigidBodyComponent->SetMass(1.f);
	RigidBodyComponent->SetupBuoyancyCircles();


	FireControlComponent->InsertWeaponSlot("Main Gun", WeaponSlot());
	FireControlComponent->InsertWeaponSlot("Rear Gun", WeaponSlot());

	CWeapon* MainGun = CreateComponent<CWeapon>();
	MainGun->SetOffset(Vector2(100.f, 20.f));
	MainGun->MakeCollisionBox(Vector2(0.f), Vector2(15.f));

	CWeapon* RearGun = CreateComponent<CWeapon>();
	RearGun->SetOffset(Vector2(-100.f, 20.f));
	RearGun->MakeCollisionBox(Vector2(15.f));

	UnPossess();

}