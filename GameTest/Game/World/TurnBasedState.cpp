#include "stdafx.h"
#include "TurnBasedState.h"
#include "../Object/Ship.h"
#include "../../Engine/Object/Controller.h"
#include "../GameUI.h"


TurnBasedGameState::TurnBasedGameState(World* InWorld) : GameState(InWorld) 
{
	PauseMenu = GetWorld()->GetWorldObjectManager()->CreateCanvas<UIPauseCanvas>();
	PauseMenu->Active = false;
};

/// <summary>
/// Handles turn status and game logic
/// </summary>
/// <param name="DeltaTime"></param>
void TurnBasedGameState::Update(float DeltaTime)
{
	//Super
	GameState::Update(DeltaTime);

	//On end
	if (CurrentState == int(ETurnState::End))
	{
		EndTurn();
	}

}

void TurnBasedGameState::OnBegin()
{
	//Super
	GameState::OnBegin();

	

}

/// <summary>
/// Traverses the ship to next in fleet
/// </summary>
/// <returns></returns>
Ship* TurnBasedGameState::GetNextFleetShip()
{
	//Get player ref
	Player& ThisPlayer = GetCurrentPlayer();

	//Traverse
	ThisPlayer.ShipIndex = MathOps::IndexShift(ThisPlayer.ShipIndex, 1, ThisPlayer.Fleet.size());

	//Get current
	return GetCurrentFleetShip();
}

/// <summary>
/// 
/// </summary>
/// <returns></returns>
Ship* TurnBasedGameState::GetPreviousFleetShip()
{
	//Get player ref
	Player& ThisPlayer = GetCurrentPlayer();

	//Traverse
	ThisPlayer.ShipIndex = MathOps::IndexShift(ThisPlayer.ShipIndex, -1, ThisPlayer.Fleet.size());

	//Get current
	return GetCurrentFleetShip();
}

/// <summary>
/// Ends turn and preps for next player
/// </summary>
void TurnBasedGameState::EndTurn()
{
	//Get current player and reset everything
	for (auto& Ship : GetCurrentPlayer().Fleet)
	{
		Ship->EndTurn();
	}

	GetNextPlayer();

	GetCurrentPlayer().LinkedController->Possess(GetCurrentPlayer().Fleet[0]);

	CurrentState = 0;


}

/// <summary>
/// Register a new player profile
/// </summary>
/// <param name="InShip"></param>
void TurnBasedGameState::RegisterController(Controller* InController, int PlayerID)
{
	Players.push_back(Player(InController));
	InController->SetPlayerID(Players.size() - 1);
}

void TurnBasedGameState::PossessShip(Ship* InShip)
{
	//If there is an active ship, unpossess
	if (GetCurrentPlayer().ActiveShip) 
		GetCurrentPlayer().ActiveShip->UnPossess();

	InShip->Possess();
}

void TurnBasedGameState::ClearPossession()
{
}

/// <summary>
/// A custom handler extending to include pause menu functionality
/// </summary>
/// <param name="InEvent"></param>
/// <param name="DeltaTime"></param>
void TurnBasedGameState::DefaultEventHandler(std::shared_ptr<Event> InEvent, float DeltaTime)
{
	//Super
	GameState::DefaultEventHandler(InEvent, DeltaTime);

	//Close pause
	if (InEvent->GetEventType() == "ClosePauseCanvas")
	{
		if (PauseMenu) PauseMenu->Shutdown();
	}

	//Close pause
	if (InEvent->GetEventType() == "OpenPauseCanvas")
	{
		if (PauseMenu) PauseMenu->OnBegin();
	}
}
