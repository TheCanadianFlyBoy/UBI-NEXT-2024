#pragma once
/*
*	ANGRY SHIPS - Ship
*	Archetype for all ships in the game
*
*/

#include "../../Engine/Object/Actor.h"
#include "../Component/WeaponComponent.h"

class CSprite;
class CFireControl;
class CRigidBody;
class CHealth;
struct Player;


class Ship : public Actor
{
	friend class GameState;

public:
	//Class Name
	inline virtual const char* GetObjectClassName() override { return GetStaticClassName(); }
	inline static const char* GetStaticClassName() { return "Actor"; }


	Ship(World* InWorld);

	//Accessible components for easy usage
	CSprite* SpriteComponent = nullptr;
	CRigidBody* RigidBodyComponent = nullptr;
	CFireControl* FireControlComponent = nullptr;
	CHealth* HealthComponent = nullptr;


	//Action
	inline bool CanUseAction() { return ActionPoints > 0; }
	inline bool UseAction(int Points = 1) {
		if (ActionPoints - Points >= 0) 
		{
			ActionPoints--; 
			return true;
		}
		return false;
	}
	inline void EndTurn() { ActionPoints = ActionsMax; }
	inline void SetActionPointMax(unsigned int Actions) { ActionsMax = Actions; ActionPoints = Actions; }
	inline int GetActionPointsRemaining() { return ActionPoints; }
	inline int GetActionPointsMax() { return ActionsMax; }

	//Toggle for Firecontol
	void Possess();
	void UnPossess();

	inline Player* GetPlayer() { return PlayerReference; }
	inline void SetPlayer(Player* InPlayer) { PlayerReference = InPlayer; }

	//TODO query and move

protected: //Members
	//How many action points the ship has
	int ActionPoints = 1;
	int ActionsMax = 1;

	int MovementCost = 1;

	Player* PlayerReference = nullptr;

};

//Default Destroyer
class Destroyer : public Ship
{
public:
	Destroyer(World* InWorld);
};

class Gunboat : public Ship
{
public:
	Gunboat(World* InWorld);

	virtual void Update(float DeltaTime) { Ship::Update(DeltaTime); };

};

class Corvette : public Ship
{
public:
	Corvette(World* InWorld);

};