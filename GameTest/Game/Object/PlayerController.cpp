#include "stdafx.h"
#include "PlayerController.h"
#include "Ship.h"
#include "../Component/FireControlComponent.h"
#include "../../Engine/Engine.h"
#include "../World/TurnBasedState.h"
#include "../World/GameWorld.h"

void PlayerController::OnBegin()
{
	Controller::OnBegin();
	
	//Save state pointer (static is fine since this should only happen once, and is crucial)
	State = static_cast<TurnBasedGameState*>(ThisWorld->GetWorldGameState());
}

/// <summary>
/// Handle parsing inputs
/// </summary>
/// <param name="DeltaTime"></param>
void PlayerController::Update(float DeltaTime)
{
	//Super
	Controller::Update(DeltaTime);

	if (App::IsKeyPressed(VK_LCONTROL)) EventManager::GetInstance()->AddEvent(std::make_shared<LoadLevelEvent>(ENGINE->CreateWorld<GameWorld>()));

	//Case: not our turn
	if (State->GetCurrentPlayerID() != PlayerID)
	{
		//Possessish
		if (State->GetCurrentFleetShip()) SetActorLocation(State->GetCurrentFleetShip());
		else SetActorLocation(State->GetCurrentPlayer().Fleet[0]);

		return;
	}

	//Keep within map params
	ClampLocation();

	//Nullguard
	if (!PossessedShip) return;
	
	//Handle Edge Scroll
	HandleEdgeScroll(DeltaTime);

	
	//Snap back to fleet
	if (ENGINE->CheckButton(XINPUT_GAMEPAD_Y)) 
	{
		SetActorLocation(PossessedShip->GetActorLocation());
		GetWorld()->GetActiveCamera()->SetTarget(nullptr);
	}

		//Cast to state, static since we absolutely need the correct game state
	TurnBasedGameState* State = static_cast<TurnBasedGameState*>(GetWorld()->GetWorldGameState());

	//If we can pass inputs...
	if (GetWorld()->GetWorldGameState()->CanPassControllerInputs())
	{
		
	
		switch (State->GetTurnState())
		{
		case ETurnState::Select:
			{
				SelectUpdate(DeltaTime);
				break;
			}
		case ETurnState::Action:
			{
				//Handle action phase
				ActionUpdate(DeltaTime);
				break;
			}
		}
	}

	//End turn
	if (ENGINE->CheckButton(XINPUT_GAMEPAD_BACK, true))
	{
		UnPossess();
		State->SetTurnState(ETurnState::End);
	}



}


/// <summary>
/// Handle select gameplay inputs
/// </summary>
/// <param name="DeltaTime"></param>
void PlayerController::SelectUpdate(float DeltaTime)
{
	TurnBasedGameState* State = static_cast<TurnBasedGameState*>(GetWorld()->GetWorldGameState());

	
	//Move between ships
	if (ENGINE->CheckButton(XINPUT_GAMEPAD_DPAD_LEFT, true))
	{
		Ship* NewShip = State->GetPreviousFleetShip();
		Possess(NewShip);
		SetActorLocation(NewShip);
	}
	if (ENGINE->CheckButton(XINPUT_GAMEPAD_DPAD_RIGHT, true))
	{
		Ship* NewShip = State->GetPreviousFleetShip();
		SetActorLocation(NewShip);
	}

	//Handle selecting and moving into action phase
	if (ENGINE->CheckButton(XINPUT_GAMEPAD_A, true))
	{
		Possess(State->GetCurrentFleetShip());
		State->SetTurnState(ETurnState::Action);
	}




}

/// <summary>
/// Update during action phase
/// </summary>
/// <param name="DeltaTime"></param>
void PlayerController::ActionUpdate(float DeltaTime)
{
	TurnBasedGameState* State = static_cast<TurnBasedGameState*>(GetWorld()->GetWorldGameState()); //TODO refactor
	CFireControl& FireControlComponent = *PossessedShip->FireControlComponent;

	if (CurrentControlScheme == EControlType::Mouse)
	{
		//Set target position
		FireControlComponent.SetAimPoint(ENGINE->GetMouseWorldPosition());

	}
	else  //Controller defaults
	{
		//Increment Aim
		FireControlComponent.AddAzimuth(ENGINE->GetLeftStick().y * DeltaTime * 0.001f);
	}


	//Handle Weapon Swap
	if (ENGINE->CheckButton(XINPUT_GAMEPAD_DPAD_UP, true))
		FireControlComponent.GetNextWeapon();
	if (ENGINE->CheckButton(XINPUT_GAMEPAD_DPAD_DOWN, true))
		FireControlComponent.GetPreviousWeapon();
	//Handle firing
	if (ENGINE->CheckButton(XINPUT_GAMEPAD_A, true))
	{
		//Attempt to fire
		if (PossessedShip->UseAction())
		{
			FireControlComponent.Fire();
		}
	}

	//Handle Reselect ship
	//Handle firing
	if (ENGINE->CheckButton(XINPUT_GAMEPAD_B, true))
	{
		State->SetTurnState(ETurnState::Select);
	}

}

/// <summary>
/// Keeps the actor within an arbitrary bounding area
/// </summary>
void PlayerController::ClampLocation()
{
	//Keep in bounds
	Vector2 ClampedLocation = GetActorLocation();
	ClampedLocation.x = MathOps::FClamp(ClampedLocation.x, 0, WorldBounds.x);
	ClampedLocation.y = MathOps::FClamp(ClampedLocation.y, 0, WorldBounds.y);
	SetActorLocation(ClampedLocation);
}

/// <summary>
/// Does edge scrolling for camera
/// </summary>
/// <param name="DeltaTime"></param>
void PlayerController::HandleEdgeScroll(float DeltaTime)
{
	//Get position, edge zone, and speed
	Vector2 MouseScreenPosition = ENGINE->GetMouseScreenPosition();
	Vector2 EdgeScrollZone = Vector2(20.f, 20.f);
	float HorizontalScrollSpeed = 10.0f;

	//Calculate scroll
	float ScrollX = float(MouseScreenPosition.x > APP_VIRTUAL_WIDTH - EdgeScrollZone.x) - (MouseScreenPosition.x < 0 + EdgeScrollZone.x);
	float ScrollY = float(MouseScreenPosition.y > APP_VIRTUAL_HEIGHT - EdgeScrollZone.y) - (MouseScreenPosition.y < 0 + EdgeScrollZone.y);

	//Implement
	AddActorLocation((Vector2(ScrollX, ScrollY) + ENGINE->GetRightStick()) * HorizontalScrollSpeed * DeltaTime * 0.01f);
}

/// <summary>
/// When a ship is possess
/// </summary>
/// <param name="InActor">Ship to possess</param>
void PlayerController::OnPossess(Actor* InActor)
{
	//Super
	Controller::OnPossess(InActor);

	//Cast so we don't have to recast later, as well as allow for error checking (nullguard)
	PossessedShip = dynamic_cast<Ship*>(InActor);

}

/// <summary>
/// When a ship is unpossessed
/// </summary>
void PlayerController::OnUnPossess()
{
	//Super
	Controller::OnUnPossess();

	//Set ship to null
	PossessedShip = nullptr;

}
