#pragma once
/*
*	ANGRY SHIPS - Projectile
*	Basic projectile logic actor
*
*/

#include "../../Engine/Object/Controller.h"

class Ship; class TurnBasedGameState;

class Projectile;

class AIController : public Controller
{
public:
	//Constructor
	AIController(World* InWorld) : Controller(InWorld) {};


	virtual void OnBegin() override;

	virtual void Update(float DeltaTime) override;

	virtual void OnPossess(Actor* InActor) override;
	virtual void OnUnPossess() override;


	Vector2 EstimateTrajectory();

	virtual void SelectPhase(float DeltaTime);
	virtual void ActionPhase(float DeltaTime);

	TurnBasedGameState* State;

	Vector2 LastInput = Vector2(-1.f, 1.f);
	Vector2 DifferenceToTarget = Vector2(0.f);
	float DistanceToTarget = 0.f;
	float AngleAdjustment = 0.f;
	float DistanceToNearest = 0.f;

	Vector2 Impact = Vector2(0.f);

	float WaitLength = 0.5f;
	float WaitTimer = 0.f;

	Ship* PossessedShip = nullptr;
	Projectile* TrackedShot;



};