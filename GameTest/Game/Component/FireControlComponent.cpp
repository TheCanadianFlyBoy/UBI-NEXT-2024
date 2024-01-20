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
	CControllerBase::Update(DeltaTime);

	//Handle controller inputs for aiming
	//Mouse
	if (CurrentControlScheme == EControlType::Mouse)
	{
		//Set target position
		AimVector = ENGINE->GetMouseWorldPosition() - Owner->GetEntityLocation();
		AimVector = AimVector.GetNormalized();

	}
	else  //Controller defaults
	{
		//Increment Aim
		AimAngle += App::GetController().GetLeftThumbStickY() * DeltaTime * TraversalRate * 0.001f;
		AimAngle = MathOps::FClamp(AimAngle, PI / -2.f, PI / 2.f);

		AimVector.x = cosf(AimAngle);
		AimVector.y = sinf(AimAngle);
		AimVector = AimVector.GetNormalized();
	}

	//Handle weapon swap
	if (App::GetController().CheckButton(APP_PAD_EMUL_DPAD_UP)) 
		GetNextWeapon();
	if (App::GetController().CheckButton(APP_PAD_EMUL_DPAD_DOWN)) 
		GetPreviousWeapon();

	bool g = App::GetController().CheckButton(VK_LBUTTON, true);
	if (g)
	{
		g = true;
	}

	//Handle firing
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_A) || App::GetController().CheckButton(XINPUT_GAMEPAD_B))
	{
		//Empty//nullcheck
		if (!AvailableWeapons.empty() && CurrentWeapon->second.Weapon)
		{
			GetCurrentWeapon()->Fire(AimVector);
		}
	}

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