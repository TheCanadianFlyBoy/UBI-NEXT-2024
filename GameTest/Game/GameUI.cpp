#include "stdafx.h"
#include "../Engine/Common.h"
#include "GameUI.h"
#include "Object/Ship.h"
#include "Component/FireControlComponent.h"

/// <summary>
/// Renders aiming information
/// </summary>
void UIAimPoint::Render()
{
	//Get Positioning
	Vector2 CentrePoint = Vector2(APP_VIRTUAL_WIDTH / 2, APP_VIRTUAL_HEIGHT / 8);
	Vector2 Dimensions = Vector2(APP_VIRTUAL_WIDTH / 2, APP_VIRTUAL_HEIGHT / 3);
	//Draw box
	Debug::DrawRectangle(CentrePoint, Vector2(APP_VIRTUAL_WIDTH / 2, APP_VIRTUAL_HEIGHT / 3));

	CFireControl& FireControl = *CurrentShip->FireControlComponent;

	if (CurrentShip && CurrentShip->Active)
	{ 
		DrawAzumith();
		DrawWeaponSelect();
		//Debug::DrawLine(CentrePoint, CentrePoint + FireControl.GetAimVector() * 20.f);
	}
	else
	{
		Debug::DrawText(CentrePoint - Vector2(100.f, 0.f), "OFFLINE", Color3(1.f, 0.f, 0.f));
	}

}


//Draw DPAD and Azumith
void UIAimPoint::DrawAzumith()
{
	//Get Positioning
	Vector2 CentrePoint = Vector2(APP_VIRTUAL_WIDTH / 2, APP_VIRTUAL_HEIGHT / 8);
	Vector2 Dimensions = Vector2(APP_VIRTUAL_WIDTH / 2, APP_VIRTUAL_HEIGHT / 3);

	Vector2 AzumithCentre = CentrePoint + Vector2(Dimensions.x / 3.f, 0.f);

	//Fire Control
	CFireControl& FireControl = *CurrentShip->FireControlComponent;

	//Draw DPAD
	Debug::DrawRectangle(AzumithCentre, Vector2(40.f, 120.f), Color3(0.2f, 0.2f, 0.2f));
	Debug::DrawRectangle(AzumithCentre, Vector2(120.f, 40.f), Color3(0.2f, 0.2f, 0.2f));


	//Draw the actual azumith display
	Debug::DrawLine(AzumithCentre, AzumithCentre + FireControl.GetAimVector() * 60.f);
	Debug::DrawCircle(AzumithCentre, 70.f, 24, Color3(1.f, 0.4f, 0.4f));

	//Get azumith
	int AzumithAngle = int(FireControl.GetAzumithDegrees());


	Debug::DrawText(AzumithCentre + Vector2(-60.f, 90.f), "Azumith: " + std::to_string(AzumithAngle));
	Debug::DrawText(AzumithCentre + Vector2(-60.f, 150.f), "Launch: Space, A");
	

}

///Draw weapon select
void UIAimPoint::DrawWeaponSelect()
{
	//Get Positioning
	Vector2 CentrePoint = Vector2(APP_VIRTUAL_WIDTH / 2, APP_VIRTUAL_HEIGHT / 8);
	Vector2 Dimensions = Vector2(APP_VIRTUAL_WIDTH / 2, APP_VIRTUAL_HEIGHT / 3);

	//Draw Header
	Debug::DrawText(CentrePoint + Vector2(-160.f, 100.f), "Current Weapon");
	
	//Get weapon
	Debug::DrawText(CentrePoint + Vector2(-160.f, 50.f), CurrentShip->FireControlComponent->GetCurrentWeaponName());
}

//Clear for shutdown
void UIAimPoint::Shutdown()
{
	UIWidget::Shutdown();
}
