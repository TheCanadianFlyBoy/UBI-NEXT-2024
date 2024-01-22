#pragma once
/*
*	ANGRY SHIPS - Menu World
*	Main menu for Angry Ships
*
*/

#include "../../Engine/World/World.h"
#include "../GameUI.h"
#include "../ShipSelection.h"
#include "../../Engine/Managers/SpriteManager.h"

class MenuWorld : public World
{
public:
	MenuWorld() : World() { 
		UIShipSelect* Select = WorldObjectManager->CreateCanvas<UIShipSelect>();
		Select->Origin += Vector2(0.f,150.f);
		Select = WorldObjectManager->CreateCanvas<UIShipSelect>();
		Select->Origin += Vector2(0.f, 300.f);
		
		UISprite* Title = Select->AddWidget<UISprite>();
		Title->SetSprite(SpriteManager::GetInstance()->GetSprite("Title"));
		Title->SetPosition(Vector2(300.f, 600.f));

		WorldObjectManager->CreateCanvas<UIShipSelect>();
		WorldObjectManager->CreateCanvas<UIMainMenu>(); 
	};

	virtual void Render() override {
		World::Render();


	}
};