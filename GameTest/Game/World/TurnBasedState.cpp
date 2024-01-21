#include "stdafx.h"
#include "TurnBasedState.h"
#include "../Object/Ship.h"

/// <summary>
/// Handles turn status and game logic
/// </summary>
/// <param name="DeltaTime"></param>
void TurnBasedGameState::TurnBasedUpdate(float DeltaTime)
{
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
	//Unpossess

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
