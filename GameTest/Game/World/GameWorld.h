#pragma once
/*
*	ANGRY SHIPS - Game World
*	Basic combat world for Angry Ships
*
*/

#include "../../Engine/Engine.h"
#include "../../Engine/Common.h"

class Ship;


class GameWorld : public World
{
public:
	GameWorld();

	Vector2 PlayerShipLocation = Vector2(700.f, 220.f);
	Ship* PlayerShip;

	virtual void OnBegin() override;
	virtual void Update(float DeltaTime) override;
	virtual void Render() override;

};