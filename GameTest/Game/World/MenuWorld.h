#pragma once
/*
*	ANGRY SHIPS - Menu World
*	Main menu for Angry Ships
*
*/

#include "../../Engine/World/World.h"
#include "../GameUI.h"

class MenuWorld : public World
{
public:
	MenuWorld(EngineCore* InEngine) : World(InEngine) { WorldObjectManager->CreateCanvas<UIMainMenu>(); };
};