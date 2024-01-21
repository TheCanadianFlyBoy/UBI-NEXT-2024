//------------------------------------------------------------------------
// GameTest.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include <windows.h> 
#include <math.h>  
//------------------------------------------------------------------------
#include "app\app.h"
//------------------------------------------------------------------------
#include "Engine/Common.h"
#include "Game/World/GameWorld.h"
#include "Game/World/MenuWorld.h"
#include "Game/GameUI.h"

#include <functional>

enum
{
	ANIM_FORWARDS,
	ANIM_BACKWARDS,
	ANIM_LEFT,
	ANIM_RIGHT,
};
//------------------------------------------------------------------------

Actor* Player;
CRigidBody* Body;
UIButton* TestText2;

//------------------------------------------------------------------------
// Called before first update. Do any initial setup here.
//------------------------------------------------------------------------
void Init()
{
	EngineCore::GetInstance()->Initialize();

	//Register sprites
	SpriteManager::GetInstance()->RegisterNewSprite("DefaultDude", ".\\TestData\\Test.bmp", 8, 4);
	SpriteManager::GetInstance()->RegisterNewSprite("Destroyer", ".\\Game\\Resources\\Sprites\\CFB_SPR_Destroyer.png");
	SpriteManager::GetInstance()->RegisterNewSprite("Cruiser", ".\\Game\\Resources\\Sprites\\CFB_SPR_Cruiser.png");
	SpriteManager::GetInstance()->RegisterNewSprite("Battleship", ".\\Game\\Resources\\Sprites\\CFB_SPR_Battleship.png");
	SpriteManager::GetInstance()->RegisterNewSprite("Gunboat", ".\\Game\\Resources\\Sprites\\CFB_SPR_Gunboat.png");
	SpriteManager::GetInstance()->RegisterNewSprite("Corvette", ".\\Game\\Resources\\Sprites\\CFB_SPR_Corvette.png");
	SpriteManager::GetInstance()->RegisterNewSprite("Shell", ".\\Game\\Resources\\Sprites\\CFB_SPR_Shell.png");
	SpriteManager::GetInstance()->RegisterNewSprite("DestroyerHull", ".\\Game\\Resources\\Sprites\\CFB_SPR_Destroyer_CollisionArea.png");

	//Register particles
	SpriteManager::GetInstance()->RegisterNewSprite("Explosion1", ".\\Game\\Resources\\Sprites\\CFB_FX_Explosion_1.png", 6, 1);
	SpriteManager::GetInstance()->RegisterAnimation("Explosion1", 0, 0.2f, {0, 1, 2, 3, 4, 5});

	//Create Main Menu Level

	ENGINE->CreateWorld<MenuWorld>("Menu");
	ENGINE->CreateWorld<GameWorld>("Game");
	ENGINE->LoadWorld("Menu");


}

//------------------------------------------------------------------------
// Update your simulation here. deltaTime is the elapsed time since the last update in ms.
// This will be called at no greater frequency than the value of APP_MAX_FRAME_RATE
//------------------------------------------------------------------------
void Update(float DeltaTime)
{
	ENGINE->Update(DeltaTime);

	ENGINE->LateUpdate(DeltaTime);
}

//------------------------------------------------------------------------
// Add your display calls here (DrawLine,Print, DrawSprite.) 
// See App.h 
//------------------------------------------------------------------------
void Render()
{	
	ENGINE->Render();

}
//------------------------------------------------------------------------
// Add your shutdown code here. Called when the APP_QUIT_KEY is pressed.
// Just before the app exits.
//------------------------------------------------------------------------
void Shutdown()
{	
	ENGINE->Shutdown();

}
