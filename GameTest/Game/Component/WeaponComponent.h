#pragma once
/*
*	ANGRY SHIPS - Weapon Component
*	Weapon components for the game
*
*/

#include "../../Engine/Component/RigidBodyComponent.h"

class Projectile;

class CWeapon : public CRigidBody
{
	friend class CFireControl;
public:
	enum class EWeaponType {
		Cannon,
		Rocket,
		RadarMissile,
		GuidedMissile
	};

public:

	//Class Name
	inline virtual const char* GetObjectClassName() override { return GetStaticClassName(); }
	inline static const char* GetStaticClassName() { return "CRigidBody"; }

	CWeapon(Entity* InEntity);

	virtual void OnBegin() override;


	//Creates projectile
	Projectile* Fire(Vector2 FiringSolution);
	void Repeat();


	//Handle weapon updates
	virtual void Update(float DeltaTime) override;

	inline int GetActionCost() { return ActionCost; }
	inline int GetProjectileCount() { return ProjectileCount; }
	inline float GetProjectileSpeed() { return ProjectileSpeed; }
	inline float GetProjectileDamage() { return ProjectileDamage; }

protected:

	float CooldownTimer = 0.f;
	float CooldownLength = 1.f;
	
	Vector2 LastFiringSolution = Vector2(0.f);

	//Weapon Usage
	int WeaponSize = 1;
	int ActionCost = 1;
	//Projectile
	int ProjectileCount = 1;
	int CurrentProjectileBurst = 0;
	float ProjectileDamage = 10.f;
	float ProjectileSpeed = 10.f;
	//Aiming
	float AimWobble = 0.01f;

	//Defaults to cannon
	EWeaponType Type = EWeaponType::Cannon;


};

class LightFifty : public CWeapon
{
public:
	LightFifty(Entity* InEntity);
};

class AutoCannon : public CWeapon
{
public:
	AutoCannon(Entity* InEntity);
};

class DeckGun : public CWeapon
{
public:
	DeckGun(Entity* InEntity);
};