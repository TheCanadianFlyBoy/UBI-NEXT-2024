#pragma once
/*
*	ANGRY SHIPS - Fire Control Component
*	Handles inputs for generating an aimpoint
*
*/

#include "../../Engine/Component/ControllerComponent.h"

class CWeapon;

struct WeaponSlot
{
	int Size = 1;
	//std::vector<unsigned int> AllowedTypes; //TODO implement if I have time
	CWeapon* Weapon = nullptr;
};

class CFireControl : public CControllerBase
{
	friend class CWeapon;
public:
	enum class EControlType {
		Mouse,
		Controller
	};
public:
	//Class Name
	inline virtual const char* GetObjectClassName() override { return GetStaticClassName(); }
	inline static const char* GetStaticClassName() { return "CControllerBase"; }

	CFireControl(Entity* InEntity) : CControllerBase(InEntity) { };

	virtual void OnBegin() override { CControllerBase::OnBegin(), CurrentWeapon = AvailableWeapons.begin(); }
	virtual void Update(float DeltaTime) override;

	inline Vector2 GetAimVector() { return AimVector; }

public: // Weapon Management

	inline void InsertWeaponSlot(std::string Name, WeaponSlot Slot) { AvailableWeapons["Name"] = Slot; }
	//inline void RemoveWeaponSlot(std::string Name) { AvailableWeapons.erase() } TODO

	//Weapon insertion
	bool InsertWeapon(CWeapon* InWeapon);
	//Getters
	inline CWeapon* GetCurrentWeapon() { return CurrentWeapon->second.Weapon; }
	inline std::string GetCurrentWeaponSlot() { return CurrentWeapon->first; }
	/// <summary>
	/// Shorthand to iterating the weapon list to the right
	/// </summary>
	inline void GetNextWeapon() { CurrentWeapon = CurrentWeapon == AvailableWeapons.end() 
		? AvailableWeapons.begin() : 
		CurrentWeapon++; }

	/// <summary>
	/// Shorthand for iterating the weapon list to the left
	/// </summary>
	inline void GetPreviousWeapon() {
		CurrentWeapon = CurrentWeapon == AvailableWeapons.begin()
			? AvailableWeapons.end() :
			CurrentWeapon--;
	}



protected: // Members
	//Fire Control Rates of Change
	float TraversalRate = 1.f;
	//Fire Control Position
	float AimAngle = PI / 4.f;
	Vector2 AimVector = Vector2(cos(AimAngle), sin(AimAngle));
	//Fire Control Type
	EControlType CurrentControlScheme = EControlType::Controller;
	//Register of available weapons
	std::map < std::string, WeaponSlot> AvailableWeapons;
	std::map<std::string, WeaponSlot>::iterator CurrentWeapon;

};