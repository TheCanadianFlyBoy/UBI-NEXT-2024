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

/// <summary>
/// Default constructor for destroyer.
/// Complement:
/// 1x Main Gun
/// </summary>
/// <param name="InWorld"></param>
Destroyer::Destroyer(World* InWorld) : Ship(InWorld)
{
	FireControlComponent->InsertWeaponSlot("Main Gun", WeaponSlot());

	CWeapon* MainGun = CreateComponent<CWeapon>();
	MainGun->SetOffset(Vector2(100.f, 20.f));
	MainGun->MakeCollisionBox(Vector2(0.f), Vector2(15.f));
}