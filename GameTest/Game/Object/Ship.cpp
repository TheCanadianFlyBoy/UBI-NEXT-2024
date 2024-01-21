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

	//Health component for combat
	HealthComponent = CreateComponent<CHealth>();

}

//Toggles the fire control system
void Ship::Possess()
{
	//FireControlComponent->Active = true;
}

void Ship::UnPossess()
{
	//FireControlComponent->Active = false;
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

	Vector2 HullDimensions = SpriteManager::GetInstance()->GetSpriteDimensions("Destroyer");

	RigidBodyComponent->MakeCollisionBox(GetActorLocation(), HullDimensions - Vector2(HullDimensions.x * 0.1f, HullDimensions.y * .7f));
	RigidBodyComponent->SetBuoyancyCircleRadius(8);
	RigidBodyComponent->SetMass(0.5f);
	RigidBodyComponent->SetupBuoyancyCircles();

	ActionsMax = 2;

	FireControlComponent->InsertWeaponSlot("Deck Gun", WeaponSlot(3));
	FireControlComponent->InsertWeaponSlot("Autocannon", WeaponSlot(2));

	CWeapon* MainGun = CreateComponent<DeckGun>();


	CWeapon* RearGun = CreateComponent<AutoCannon>();


};

Gunboat::Gunboat(World* InWorld) : Ship(InWorld)
{
	ActionsMax = 3;
	SpriteComponent->SetSprite("Gunboat");
	SpriteComponent->SetPosition(Vector2(5, 30.f));

	Vector2 HullDimensions = SpriteManager::GetInstance()->GetSpriteDimensions("Gunboat");

	RigidBodyComponent->MakeCollisionBox(GetActorLocation(), HullDimensions - Vector2(HullDimensions.x * 0.02f, HullDimensions.y * 0.7f));
	RigidBodyComponent->SetBuoyancyCircleRadius(8.f);
	RigidBodyComponent->SetMass(1.f);
	RigidBodyComponent->SetupBuoyancyCircles();
	RigidBodyComponent->SetDensity(20.f);

	FireControlComponent->InsertWeaponSlot("AutoCannon", WeaponSlot(2));
	FireControlComponent->InsertWeaponSlot("Light .50", WeaponSlot(1));
	FireControlComponent->InsertWeaponSlot("Light .50", WeaponSlot(1));
	FireControlComponent->InsertWeaponSlot("Light .50", WeaponSlot(1));

	CWeapon* Gun = CreateComponent<AutoCannon>();
	//Gun->MakeCollisionBox(Vector2(0.f), Vector2(15.f));
	Gun = CreateComponent<LightFifty>();
	//Gun->MakeCollisionBox(Vector2(0.f), Vector2(15.f));
	Gun = CreateComponent<LightFifty>();
	//Gun->MakeCollisionBox(Vector2(0.f), Vector2(15.f));
	Gun = CreateComponent<LightFifty>();
	//Gun->MakeCollisionBox(Vector2(0.f), Vector2(15.f));
};

Corvette::Corvette(World* InWorld) : Ship(InWorld)
{
	SpriteComponent->SetSprite("Corvette");
	SpriteComponent->SetPosition(Vector2(5, 30.f));

	Vector2 HullDimensions = SpriteManager::GetInstance()->GetSpriteDimensions("Corvette");

	RigidBodyComponent->MakeCollisionBox(GetActorLocation(), HullDimensions - Vector2(HullDimensions.x * 0.02f, HullDimensions.y * .7f));
	RigidBodyComponent->SetOffset(Vector2(0.f, 8.f));
	RigidBodyComponent->SetBuoyancyCircleRadius(8.f);
	RigidBodyComponent->SetMass(1.f);
	RigidBodyComponent->SetupBuoyancyCircles();
	RigidBodyComponent->SetDensity(20.f);

	ActionsMax = 4;

	FireControlComponent->InsertWeaponSlot("Autocannon", WeaponSlot());

	CWeapon* MainGun = CreateComponent<AutoCannon>();

};


Cruiser::Cruiser(World* InWorld) : Ship(InWorld)
{
	FireControlComponent->InsertWeaponSlot("Autocannon", WeaponSlot(2));
	CreateComponent<AutoCannon>();
	FireControlComponent->InsertWeaponSlot("Hydra Rockets", WeaponSlot(2));
	CreateComponent<HydraRockets>();
	FireControlComponent->InsertWeaponSlot("Light .50", WeaponSlot(2));
	CreateComponent<LightFifty>();
	SpriteComponent->SetSprite("Cruiser");
	SpriteComponent->SetPosition(Vector2(5, 30.f));

	Vector2 HullDimensions = SpriteManager::GetInstance()->GetSpriteDimensions("Cruiser");

	RigidBodyComponent->MakeCollisionBox(GetActorLocation(), HullDimensions - Vector2(HullDimensions.x * 0.02f, HullDimensions.y * .7f));
	RigidBodyComponent->SetOffset(Vector2(0.f, 8.f));
	RigidBodyComponent->SetBuoyancyCircleRadius(8.f);
	RigidBodyComponent->SetMass(1.f);
	RigidBodyComponent->SetupBuoyancyCircles();
	RigidBodyComponent->SetDensity(20.f);

	ActionsMax = 3;

	//

}
