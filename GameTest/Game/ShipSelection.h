#pragma once
/*
*	ANGRY SHIPS - Ship Select
*	UI Widget for selecting your fleet
*
*/

#include "../Engine/UI/UICanvas.h"
#include "../Engine/UI/UIWidget.h"

class UIShipSelectButton;

class UIShipSelect : public UICanvas
{
public:

	UIShipSelect();

	UISprite* Display;

	virtual void Shutdown() override;

	virtual void Update(float DeltaTime) override;

	int Index = 0;

	//Container
	std::vector<std::pair<std::string, UISprite*>> Ships;

	UIShipSelectButton* LeftButton;
	UIShipSelectButton* RightButton;

	Vector2 Origin = Vector2(800.f, 200.f);

};

class UIShipSelectButton : public UIButton
{
public:
	UIShipSelectButton() : UIButton() {
		SetDimensions(Vector2(30.f));
	};


	UIShipSelect* MySelector = nullptr;

	int Direction = 1;

	virtual void  Callback() override {
		if (MySelector)
		{
			MySelector->Index = MySelector + Direction < 0 ? MySelector->Ships.size() - 1 : (MySelector->Index + 1) % MySelector->Ships.size();
		}

	}

	
};
