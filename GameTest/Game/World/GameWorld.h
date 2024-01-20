#pragma once
/*
*	ANGRY SHIPS - Game World
*	Basic combat world for Angry Ships
*
*/

#include "../../CFB_Engine/Engine.h"
#include "../../CFB_Engine/Common.h"


class GameWorld : public World
{
public:
	GameWorld(EngineCore* Engine);


	void FireCannon();

	Vector2 PlayerShipLocation = Vector2(700.f, 200.f);
	Actor* PlayerShip;


	virtual void Update(float DeltaTime) override;
	virtual void Render() override;

};