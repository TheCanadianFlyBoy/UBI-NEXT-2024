#pragma once
/*
*	ANGRY SHIPS - UI
*	Master file containing UI widgets for gameplay
*
*/

#include "../Engine/Engine.h"
#include "../Engine/UI/UICanvas.h"
#include "../Engine/UI/UIWidget.h"
#include "Object/PlayerController.h"

class Ship;

class UIAimPoint; class UIPlayerDisplay;

class UIPlayButton : public UIButton
{
public:
	UIPlayButton() : UIButton() {};
	virtual void Callback() override;

};

class UIExitButton : public UIButton
{
public:
	UIExitButton() : UIButton() {};
	virtual void Callback() override { exit(0); };

};

class UIMainMenu : public UICanvas
{
public:
	UIMainMenu();

	UIPlayButton* PlayButton;
	UIExitButton* ExitButton;

};




class UIPauseCanvas : public UICanvas
{
public:
	UIPauseCanvas();

	UIButton* ResumeButton;
	UIButton* MenuButton;

};

class UIHUDCanvas : public UICanvas
{
public:
	UIHUDCanvas();

	UIAimPoint* AimPointWidget = nullptr;
	UIPlayerDisplay* PlayerDisplayWidget = nullptr;
};

class UIAimPoint : public UIWidget
{
public:
	UIAimPoint(UICanvas* InCanvas = nullptr) : UIWidget(InCanvas) {}
	
	//Draw call
	virtual void Render() override;
	//Update internals
	virtual void Update(float DeltaTime) override;

	virtual void Shutdown() override;

	//Set current ship to base UI off of
	inline void SetCurrentShip(Ship* InShip) { CurrentShip = InShip; }

	inline void SetPlayerController(PlayerController* InController) { Controller = InController; };

protected:
	//Ship UI is tracking
	Ship* CurrentShip = nullptr;
	PlayerController* Controller = nullptr;

	void DrawAzumith();
	void DrawWeaponSelect();

};

class UIPlayerDisplay : public UIWidget
{
public:
	UIPlayerDisplay(UICanvas* InCanvas = nullptr) : UIWidget(InCanvas) {};

	virtual void Render() override;
};