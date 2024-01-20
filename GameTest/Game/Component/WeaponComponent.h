#pragma once
/*
*	ANGRY SHIPS - Weapon Component
*	Weapon components for the game
*
*/

#include "../../Engine/Component/RigidBodyComponent.h"


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
	void Fire(Vector2 FiringSolution);


	//Handle weapon updates
	virtual void Update(float DeltaTime) override;

protected:

	float CooldownTimer = 0.f;
	float CooldownLength = 1.f;
	
	int WeaponSize = 1;
	//Defaults to cannon
	EWeaponType Type = EWeaponType::Cannon;


};