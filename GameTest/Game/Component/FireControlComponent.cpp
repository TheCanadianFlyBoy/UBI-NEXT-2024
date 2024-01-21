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

	//Calculate bounds
	float UpperBound = bFlipAxis ? 3.f * PI / 2.f: PI / 2.f;
	float LowerBound = bFlipAxis ? PI / 2.f : -PI / 2.f;

	//Clamp aim
	AzimuthRadians = MathOps::FClamp(AzimuthRadians, LowerBound, UpperBound);

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
				Weapon->Position = itr->second.Offset;
				return true;
			}
		}
	}

	return false;
}