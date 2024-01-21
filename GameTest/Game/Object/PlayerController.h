#pragma once
/*
*	ANGRY SHIPS - Player Controller
*	Handles incoming control inputs
*
*/

#include "../../Engine/Object/Controller.h"

class Ship; class TurnBasedGameState;


class PlayerController : public Controller
{
enum class EControlType {
	Mouse,
	Controller
};
public: // COMMON
	//Constructor
	PlayerController(World* InWorld) : Controller(InWorld) {};

	virtual void OnBegin() override;
	virtual void Update(float DeltaTime) override;

	//Location Methods
	void ClampLocation();
	void HandleEdgeScroll(float DeltaTime);

	//Gameplay Loop Methods
	void SelectUpdate(float DeltaTime);
	void ActionUpdate(float DeltaTime);
	

	virtual void OnPossess(Actor* InActor) override;
	virtual void OnUnPossess() override;

	//Shorthand to avoid casts
	Ship* PossessedShip;

	EControlType CurrentControlScheme = EControlType::Controller;

	Vector2 WorldBounds = Vector2(20000.f, 350.f);

	TurnBasedGameState* State = nullptr;

};