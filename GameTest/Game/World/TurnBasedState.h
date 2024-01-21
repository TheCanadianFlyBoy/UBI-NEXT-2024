#pragma once
/*
*	ANGRY SHIPS - Turn Based State
*	Handles turns and passing controller inputs
*
*/

#include "../../Engine/State/GameState.h"

class Ship;

struct Player {
	//Ships
	std::vector<Ship*> Fleet;

	Ship* ActiveShip = nullptr;

	unsigned int ShipIndex = 0;

	//End turn flag
	bool EndTurn = false;

};

enum class ETurnState : int
{
	Select,
	Action,
	End
};

class TurnBasedGameState : public GameState
{
public:
	

public:
	//Class Name
	inline virtual const char* GetObjectClassName() override { return GetStaticClassName(); }
	inline static const char* GetStaticClassName() { return "Ship"; }

	TurnBasedGameState(World* InWorld) : GameState(InWorld) {};


	//Custom Update
	virtual void TurnBasedUpdate(float DeltaTime);
	//Fleet management
	inline void RegisterShip(Ship* InShip, unsigned int PlayerID) { 
		if (PlayerID < Players.size())
		{
			Players[PlayerID].Fleet.push_back(InShip);
		}
		else
		{
			//Create struct with ship in array
			Players.push_back({ {InShip}, nullptr, 0, false });
		}
	
	}

	//Fleet Access
	inline Ship* GetCurrentFleetShip() { return GetCurrentPlayer().Fleet[GetCurrentPlayer().ShipIndex]; };
	Ship* GetNextFleetShip();
	Ship* GetPreviousFleetShip();

	//Turn Ending
	void EndTurn();

	//Turn State
	inline void SetTurnState(ETurnState State) { CurrentState = int(State); }
	inline ETurnState GetTurnState() { return ETurnState(CurrentState); }
	// Player Getter
	inline Player& GetCurrentPlayer() { return Players[CurrentPlayerID]; }
protected: // Methods
	inline void GetNextPlayer() { CurrentPlayerID = CurrentPlayerID + 1 < Players.size() ? CurrentPlayerID + 1 : 0; }

	void PossessShip(Ship* InShip);
	void ClearPossession();

protected: // Members
	std::vector<Player> Players;
	unsigned int CurrentPlayerID = 0;
};