#pragma once
/*
*	ANGRY SHIPS - Menu World
*	Main menu for Angry Ships
*
*/

#include "../../Engine/World/World.h"
#include "../GameUI.h"
#include "../ShipSelection.h"

class MenuWorld : public World
{
public:
	MenuWorld() : World() { 
		WorldObjectManager->CreateCanvas<UIShipSelect>();
		WorldObjectManager->CreateCanvas<UIMainMenu>(); 
	};
};