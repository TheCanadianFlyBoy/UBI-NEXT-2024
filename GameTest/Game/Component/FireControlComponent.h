#pragma once
/*
*	ANGRY SHIPS - Fire Control Component
*	Handles inputs for generating an aimpoint
*
*/

#include "../../Engine/Component/ControllerComponent.h"
#include "WeaponComponent.h"

class CWeapon;

struct WeaponSlot
{
	WeaponSlot(int InSize = 1) { Size = InSize; Offset = Vector2(0.f), Weapon = nullptr; };

	Vector2 Offset = Vector2(0.f);
	int Size = 1;
	//std::vector<unsigned int> AllowedTypes; //TODO implement if I have time
	CWeapon* Weapon = nullptr;
};

class CFireControl : public CInput
{
	friend class CWeapon;
public:

public:
	//Class Name
	inline virtual const char* GetObjectClassName() override { return GetStaticClassName(); }
	inline static const char* GetStaticClassName() { return "CInput"; }

	CFireControl(Entity* InEntity) : CInput(InEntity) { };

	//Overrides
	virtual void OnBegin() override { CInput::OnBegin(); }
	virtual void Update(float DeltaTime) override;

	//Aim setters
	inline void AddAzimuth(float InAzimuth) { AzimuthRadians += InAzimuth * TraversalRate; }
	inline void SetAzimuth(float inAzimuth) { AzimuthRadians = inAzimuth; }
	inline void SetAimPoint(Vector2 InVector) { AimVector = acos((InVector - GetTurretPosition()).x); }
	//Aim Getters
	inline Vector2 GetAimVector() { return AimVector; }
	inline float GetAzimuthRadians() { return AzimuthRadians; }
	inline float GetAzimuthDegrees() { return MathOps::RadiansToDegrees(AzimuthRadians); }

public: // Weapon Management
	//Fire!
	inline Projectile* Fire() { 
	if (GetCurrentWeapon()) 
		return GetCurrentWeapon()->Fire(GetAimVector()); 
	
	return nullptr; }

	//Weapon Slot Insertion
	inline void InsertWeaponSlot(std::string Name, WeaponSlot Slot) { AvailableWeapons.push_back(std::pair<std::string, WeaponSlot>(Name, Slot)); }
	//inline void RemoveWeaponSlot(std::string Name) { AvailableWeapons.erase() } TODO

	//Weapon insertion
	bool InsertWeapon(CWeapon* InWeapon);
	//Getters
	inline CWeapon* GetCurrentWeapon() { return AvailableWeapons[WeaponIndex].second.Weapon; }
	inline WeaponSlot GetCurrentWeaponSlot() { return AvailableWeapons[WeaponIndex].second; }
	inline std::string GetCurrentWeaponName() { return AvailableWeapons[WeaponIndex].first; }
	/// <summary>
	/// Shorthand to iterating the weapon list to the right
	/// </summary>
	inline void GetNextWeapon() { WeaponIndex = WeaponIndex + 1 < AvailableWeapons.size() ? WeaponIndex + 1 : 0; }

	/// <summary>
	/// Shorthand for iterating the weapon list to the left
	/// </summary>
	inline void GetPreviousWeapon() { WeaponIndex = int(WeaponIndex - 1 >= 0  ? WeaponIndex - 1 : AvailableWeapons.size() - 1); }

	//Flip axis around for other facing
	inline void FlipAxis() { bFlipAxis = !bFlipAxis; }

protected: // Methods

	inline Vector2 GetTurretPosition() { 
		if (GetCurrentWeapon()) return GetCurrentWeapon()->GetPosition();
		return Vector2(0.f);
	}

protected: // Members
	//Fire Control Rates of Change
	float TraversalRate = 1.f;
	//Fire Control Position
	float AzimuthRadians = PI / 4.f;
	Vector2 AimVector = Vector2(cos(AzimuthRadians), sin(AzimuthRadians));
	//Register of available weapons
	std::vector<std::pair<std::string, WeaponSlot>> AvailableWeapons;
	int WeaponIndex = 0;

	bool bFlipAxis = false;

};