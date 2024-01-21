#include "stdafx.h"
#include "../../Engine/Common.h"
#include "FireControlComponent.h"
#include "WeaponComponent.h"

/// <summary>
/// Handles inputs and traverses the gun based on said inputs
/// </summary>
/// <param name="DeltaTime"></param>
void CFireControl::Update(float DeltaTime)
{
	CInput::Update(DeltaTime);

	//Clamp aim
	AzimuthRadians = MathOps::FClamp(AzimuthRadians, -PI / 2.f, PI / 2.f);

	AimVector = Vector2(cosf(AzimuthRadians), sinf(AzimuthRadians));

}


bool CFireControl::InsertWeapon(CWeapon* Weapon)
{
	//Iterate
	for (auto& itr = AvailableWeapons.begin(); itr != AvailableWeapons.end(); ++itr)
	{
		//Found an empty slot
		if (itr->second.Weapon == nullptr)
		{
			//Valid size
			if (Weapon->WeaponSize <= itr->second.Size)
			{
				//Insert
				itr->second.Weapon = Weapon;
				return true;
			}
		}
	}

	return false;
}