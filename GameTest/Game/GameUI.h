#pragma once
/*
*	ANGRY SHIPS - UI
*	Master file containing UI widgets for gameplay
*
*/

#include "../Engine/Engine.h"
#include "../Engine/UI/UICanvas.h"
#include "../Engine/UI/UIWidget.h"

class Ship;

class UIAimPoint : public UIWidget
{
public:
	UIAimPoint(UICanvas* InCanvas = nullptr) : UIWidget(InCanvas) {}
	
	//Draw call
	virtual void Render() override;
	//Update internals

	virtual void Shutdown() override;

	//Set current ship to base UI off of
	inline void SetCurrentShip(Ship* InShip) { CurrentShip = InShip; }

protected:
	//Ship UI is tracking
	Ship* CurrentShip = nullptr;

	void DrawAzumith();

};