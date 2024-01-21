#include "stdafx.h"
#include "../Engine/Common.h"
#include "GameUI.h"
#include "Object/Ship.h"
#include "Component/FireControlComponent.h"
#include "World/TurnBasedState.h"
#include "World/GameWorld.h"


/// <summary>
/// Set up the default main menu canvas
/// </summary>
UIMainMenu::UIMainMenu() : UICanvas()
{
	Vector2 CentrePoint = Vector2(APP_VIRTUAL_WIDTH / 2, APP_VIRTUAL_HEIGHT / 2);

	PlayButton = AddWidget<UIButton>();
	PlayButton->SetPosition(CentrePoint);
	PlayButton->SetDimensions(Vector2(200.f, 50.f));
	PlayButton->SetText("Play");

	ExitButton = AddWidget<UIButton>();
	ExitButton->SetPosition(CentrePoint - Vector2(0.f, 100.f));
	ExitButton->SetDimensions(Vector2(200.f, 50.f));
	ExitButton->SetText("Exit");

	ExitButton->CallbackFunction = []() { exit(0); };
	PlayButton->CallbackFunction = []() { EventManager::GetInstance()->AddEvent(std::make_shared<LoadLevelEvent>("Game")); };

};

UIPauseCanvas::UIPauseCanvas() : UICanvas()
{
	Vector2 CentrePoint = Vector2(APP_VIRTUAL_WIDTH / 2, APP_VIRTUAL_HEIGHT / 2);

	ResumeButton = AddWidget<UIButton>();
	ResumeButton->SetPosition(CentrePoint);
	ResumeButton->SetDimensions(Vector2(200.f, 50.f));
	ResumeButton->SetText("Resume");

	MenuButton = AddWidget<UIButton>();
	MenuButton->SetPosition(CentrePoint - Vector2(0.f, 100.f));
	MenuButton->SetDimensions(Vector2(200.f, 50.f));
	MenuButton->SetText("Quit to Menu");

	MenuButton->CallbackFunction = []()   { exit(0); };
	ResumeButton->CallbackFunction = []() { EventManager::GetInstance()->AddEvent(std::make_shared<LoadLevelEvent>("Game")); };
}


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

	//Nullguard
	if (CurrentShip)
	{
		//If ship is active and we're on a turn
		if (CurrentShip->Active && ENGINE->GetCurrentWorld()->GetWorldGameState()->GetCurrentState() == int(ETurnState::Action))
		{
			CFireControl& FireControl = *CurrentShip->FireControlComponent;
			DrawAzumith();
			DrawWeaponSelect();
			//Debug::DrawLine(CentrePoint, CentrePoint + FireControl.GetAimVector() * 20.f);
		}
		else { //Draw Ship Overview

			Debug::DrawText(CentrePoint - Vector2(200.f, -80.f), "Select Ship:");
			
			//
		}
	}
	else //Fail case, draw offline
	{
		Debug::DrawText(CentrePoint - Vector2(100.f, 0.f), "OFFLINE", Color3(1.f, 0.f, 0.f));
	}

}

/// <summary>
/// Fetch updated current ship
/// </summary>
/// <param name="DeltaTime"></param>
void UIAimPoint::Update(float DeltaTime)
{
	if (Controller)
	{
		CurrentShip = Controller->PossessedShip;
	}
	else {
		CurrentShip = nullptr;
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
	int AzumithAngle = int(FireControl.GetAzimuthDegrees());

	//Draw text
	Debug::DrawText(AzumithCentre + Vector2(-60.f, 90.f), "Azumith: " + std::to_string(AzumithAngle));
	Debug::DrawText(AzumithCentre + Vector2(-60.f, 150.f), "Launch: Space, A");

	
	//Action Point display
	Vector2 DisplayStart = CentrePoint + Vector2(-210.f, -Dimensions.y / 4);

	Debug::DrawText(DisplayStart + Vector2(0.f, 28.f), "Action Points");

	for (int i = 0; i < CurrentShip->GetActionPointsMax(); i++)
	{
		Color3 Color = i >= CurrentShip->GetActionPointsRemaining() ? Color3(0.7f, 0.1f, 0.1f) : Color3(0.2f, 1.f, 0.2f);
		
		Debug::DrawCircle(DisplayStart + Vector2(i * 20.f, 0.f), 16.f, 8, Color);

	}
	

}

///Draw weapon select
void UIAimPoint::DrawWeaponSelect()
{
	CWeapon* CurrentWeapon = CurrentShip->FireControlComponent->GetCurrentWeapon();

	//Get Positioning
	Vector2 CentrePoint = Vector2(APP_VIRTUAL_WIDTH / 2, APP_VIRTUAL_HEIGHT / 8);
	Vector2 Dimensions = Vector2(APP_VIRTUAL_WIDTH / 2, APP_VIRTUAL_HEIGHT / 3);

	//Draw Header
	Debug::DrawText(CentrePoint + Vector2(-160.f, 100.f), "Current Weapon");
	
	//Get weapon
	Debug::DrawText(CentrePoint + Vector2(-230.f, 80.f), CurrentShip->FireControlComponent->GetCurrentWeaponName());
	Debug::DrawText(CentrePoint + Vector2(-230.f, 60.f), "AP Cost: " + std::to_string(CurrentWeapon->GetActionCost()));
	Debug::DrawText(CentrePoint + Vector2(-230.f, 40.f), "Burst: " + std::to_string(CurrentWeapon->GetProjectileCount()));
	Debug::DrawText(CentrePoint + Vector2(-230.f, 20.f), "Damage: " + std::to_string(CurrentWeapon->GetProjectileDamage()));
}

//Clear for shutdown
void UIAimPoint::Shutdown()
{
	UIWidget::Shutdown();
}

/// <summary>
/// Renders the current player number
/// </summary>
void UIPlayerDisplay::Render()
{
	TurnBasedGameState* State = dynamic_cast<TurnBasedGameState*>(ENGINE->GetCurrentWorld()->GetWorldGameState());

	//Nullguard
	if (State)
	{
		Vector2 CentrePoint = Vector2(APP_VIRTUAL_WIDTH / 2, APP_VIRTUAL_HEIGHT / 8);

		//Render
		Vector2 TextPosition = Vector2(APP_VIRTUAL_WIDTH / 2 - 200.f, APP_VIRTUAL_HEIGHT -  20.f);

		Debug::DrawText(TextPosition, "Current Player: " + std::to_string(State->GetCurrentPlayerID()));
	}

}

/// <summary>
/// Construct basic hud
/// </summary>
UIHUDCanvas::UIHUDCanvas() : UICanvas()
{
	AimPointWidget = AddWidget<UIAimPoint>();
	PlayerDisplayWidget = AddWidget<UIPlayerDisplay>();
}
