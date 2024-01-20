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
	SpriteManager::GetInstance()->RegisterNewSprite("DestroyerHull", ".\\Game\\Resources\\Sprites\\CFB_SPR_Destroyer_CollisionArea.png");

	ENGINE->LoadWorld(ENGINE->CreateWorld<GameWorld>());




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


	//Debug::DrawCircle(MouseCircle.Position, MouseCircle.Radius, 12, collision ? Color3(1.f, 0.5f, 0.f) : Color3(1.f));


}
//------------------------------------------------------------------------
// Add your shutdown code here. Called when the APP_QUIT_KEY is pressed.
// Just before the app exits.
//------------------------------------------------------------------------
void Shutdown()
{	


}
