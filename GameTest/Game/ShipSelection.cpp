#include "stdafx.h"
#include "ShipSelection.h"
#include "../Engine/Managers/SpriteManager.h"
#include "GameEvents.h"
#include "../Engine/Managers/EventManager.h"

UIShipSelect::UIShipSelect() : UICanvas()
{
	//Create tuples
	UISprite* Corvette = AddWidget<UISprite>();
	Corvette->SetSprite(SpriteManager::GetInstance()->GetSprite("Corvette"));
	UISprite* Gunboat = AddWidget<UISprite>();
	Gunboat->SetSprite(SpriteManager::GetInstance()->GetSprite("Gunboat"));
	UISprite* Destroyer = AddWidget<UISprite>();
	Destroyer->SetSprite(SpriteManager::GetInstance()->GetSprite("Destroyer"));
	UISprite* Cruiser = AddWidget<UISprite>();
	Cruiser->SetSprite(SpriteManager::GetInstance()->GetSprite("Cruiser"));

	Ships.push_back(std::make_pair<>("Corvette", Corvette));
	Ships.push_back(std::make_pair<>("Gunboat", Gunboat));
	Ships.push_back(std::make_pair<>("Destroyer", Destroyer));
	Ships.push_back(std::make_pair<>("Cruiser", Cruiser));


	//Move off screen
	for (int i = 0; i < Ships.size(); i++)
	{
		Ships[i].second->SetPosition(Vector2(-1000.f));
	}




	LeftButton = AddWidget<UIShipSelectButton>();
	LeftButton->Direction = -1;
	RightButton = AddWidget<UIShipSelectButton>();

	LeftButton->SetText("<");
	RightButton->SetText(">");

	LeftButton->MySelector = this;
	RightButton->MySelector = this;
	


}

/// <summary>
/// Send spawn event
/// </summary>
void UIShipSelect::Shutdown()
{
	EventManager::GetInstance()->AddEvent(std::make_shared<SpawnEvent>(Ships[Index].first, 0));
}

void UIShipSelect::Update(float DeltaTime)
{
	UICanvas::Update(DeltaTime);

	//Move off screen
	for (int i = 0; i < Ships.size(); i++)
	{
		Ships[i].second->SetPosition(Vector2(-1000.f));
	}


	//Get sprite
	UISprite* Sprite = Ships[Index].second;

	Vector2 Pad = Vector2(140.4, 0.f);

	//Move to position
	Sprite->SetPosition(Origin);
	LeftButton->SetPosition(Origin - Pad);
	RightButton->SetPosition(Origin + Pad);

	Debug::DrawText(Pad - Vector2(30.f, 30.f), Ships[Index].first);

}
