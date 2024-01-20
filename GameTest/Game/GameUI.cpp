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
	//Draw box
	Debug::DrawRectangle(CentrePoint, Vector2(APP_VIRTUAL_WIDTH / 2, APP_VIRTUAL_HEIGHT / 3));

	CFireControl& FireControl = *CurrentShip->FireControlComponent;

	if (CurrentShip && CurrentShip->Active)
	{ 
		DrawAzumith();

		//Debug::DrawLine(CentrePoint, CentrePoint + FireControl.GetAimVector() * 20.f);
	}
	else
	{
		Debug::DrawText(CentrePoint - Vector2(100.f, 0.f), "OFFLINE", Color3(1.f, 0.f, 0.f));
	}

}

void UIAimPoint::DrawAzumith()
{
	//Get Positioning
	Vector2 CentrePoint = Vector2(APP_VIRTUAL_WIDTH / 2, APP_VIRTUAL_HEIGHT / 8);

	//Fire Control
	CFireControl& FireControl = *CurrentShip->FireControlComponent;

	Debug::DrawLine(CentrePoint, CentrePoint + FireControl.GetAimVector() * 50.f);
	

}

//Clear for shutdown
void UIAimPoint::Shutdown()
{
	UIWidget::Shutdown();
}
