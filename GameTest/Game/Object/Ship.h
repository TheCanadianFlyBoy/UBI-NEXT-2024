#pragma once
/*
*	ANGRY SHIPS - Ship
*	Archetype for all ships in the game
*
*/

#include "../../Engine/Object/Actor.h"
#include "../Component/WeaponComponent.h"

class CSprite;
class CFireControl;
class CRigidBody;
class CHealth;

class Ship : public Actor
{
public:
	//Class Name
	inline virtual const char* GetObjectClassName() override { return GetStaticClassName(); }
	inline static const char* GetStaticClassName() { return "Ship"; }

	Ship(World* InWorld);

	//Accessible components for easy usage
	CSprite* SpriteComponent = nullptr;
	CRigidBody* RigidBodyComponent = nullptr;
	CFireControl* FireControlComponent = nullptr;
	CHealth* HealthComponent = nullptr;


protected: //Members
	

};

//Default Destroyer
class Destroyer : public Ship
{
public:
	Destroyer(World* InWorld);
};