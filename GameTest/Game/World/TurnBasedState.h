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

	//End turn flag
	bool EndTurn = false;

};

class TurnBasedGameState : public GameState
{
public:
	//Class Name
	inline virtual const char* GetObjectClassName() override { return GetStaticClassName(); }
	inline static const char* GetStaticClassName() { return "Ship"; }



	//Custom Update
	virtual void TurnBasedUpdate(float DeltaTime);
	
	void EndTurn();


	//
	inline Player GetCurrentPlayer() { return Players[CurrentPlayerID]; }
protected: // Methods
	inline void GetNextPlayer() { CurrentPlayerID = CurrentPlayerID + 1 < Players.size() ? CurrentPlayerID + 1 : 0; }

	void PossessShip(Ship* InShip);
	void ClearPossession();

protected: // Members
	std::vector<Player> Players;
	unsigned int CurrentPlayerID = 0;
};