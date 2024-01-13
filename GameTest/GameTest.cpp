//------------------------------------------------------------------------
// GameTest.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include <windows.h> 
#include <math.h>  
#include "CFB_Engine/Object/Actor.h"
#include "CFB_Engine/Component/AllComponents.h"
#include "CFB_Engine/Managers/ObjectManager.h"
#include "CFB_Engine/Managers/SpriteManager.h"
#include "CFB_Engine/World/World.h"
#include "CFB_Engine/Event/Event.h"
#include "CFB_Engine/Engine.h"
#include "CFB_Engine/World/Tilemap.h"
#include "CFB_Engine/Component/TileMovementComponent.h"
//------------------------------------------------------------------------
#include "app\app.h"
//------------------------------------------------------------------------

//------------------------------------------------------------------------
// Eample data....
//------------------------------------------------------------------------

World* world;
CSprite *testSprite;
Actor* obj;
CTransform* transform;
//ObjectManager* objmanager;
SpriteManager* sprmanager;
Engine* GameEngine;
Tilemap* map;
CTileMovement* movement;


enum
{
	ANIM_FORWARDS,
	ANIM_BACKWARDS,
	ANIM_LEFT,
	ANIM_RIGHT,
};
//------------------------------------------------------------------------

//------------------------------------------------------------------------
// Called before first update. Do any initial setup here.
//------------------------------------------------------------------------
void Init()
{
	//Instantiate Engine
	GameEngine = new Engine();
	map = new Tilemap(Vector2(5.f), Vector2(50.f));

	//Start pos
	Vector2 startPos = map->ConvertMaptoWorld(Vector2(2, 2), true);

	//Create world
	world = GameEngine->CreateWorld<World>();

	UICanvas* canvas = world->GetWorldObjectManager()->CreateCanvas<UICanvas>();
	world->GetWorldObjectManager()->CreateWidget<UIText>(canvas);

	sprmanager = world->GetEngineSpriteManager();
	//Register sprite
	sprmanager->RegisterNewSprite("spr_player", ".\\TestData\\Test.bmp", 8, 4, 2);
	float speed = 1.0f / 15.0f;
	sprmanager->RegisterAnimation("spr_player", ANIM_BACKWARDS, speed, { 0,1,2,3,4,5,6,7 });
	sprmanager->RegisterAnimation("spr_player", ANIM_LEFT, speed, { 8,9,10,11,12,13,14,15 });
	sprmanager->RegisterAnimation("spr_player", ANIM_RIGHT, speed, { 16,17,18,19,20,21,22,23 });
	sprmanager->RegisterAnimation("spr_player", ANIM_FORWARDS, speed, { 24,25,26,27,28,29,30,31 });

	//Initialize object manager

	

	obj = world->CreateEntity<Actor>();
	obj->SetActorLocation(startPos);

	CCamera* cam = obj->CreateComponent<CCamera>();

	world->SetActiveCamera(cam);
	//save transform
	transform = obj->GetComponentOfClass<CTransform>();

	testSprite = obj->CreateComponent<CSprite>();
	testSprite->SetSprite(sprmanager->GetSprite("spr_player"));
	testSprite->SetHeightAlignment(CSprite::SpriteHeightAlignment::Centre);
	
	//Setup movement
	movement = obj->CreateComponent<CTileMovement>();




	bool END = true;

}

//------------------------------------------------------------------------
// Update your simulation here. deltaTime is the elapsed time since the last update in ms.
// This will be called at no greater frequency than the value of APP_MAX_FRAME_RATE
//------------------------------------------------------------------------
void Update(float deltaTime)
{

	world->Update(deltaTime);
	

	//------------------------------------------------------------------------
	// Example Sprite Code....
	testSprite->Update(deltaTime);
	
	//Tile based movement
	Vector2 Input = Vector2(App::GetController().GetLeftThumbStickX(), App::GetController().GetLeftThumbStickY());

	movement->MoveOnTilemap(Input, map, deltaTime);

	if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_UP, false))
	{
		testSprite->SetScale(testSprite->GetScale() + 0.1f);
	}
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_DOWN, false))
	{
		testSprite->SetScale(testSprite->GetScale() - 0.1f);
	}
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_LEFT, false))
	{
		testSprite->SetRotation((testSprite->GetRotation() + 0.1f));
	}
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_RIGHT, false))
	{
		testSprite->SetRotation(testSprite->GetRotation() - 0.1f);
	}
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_A, true))
	{
		testSprite->SetAnimation(-1);
		world->GetWorldEventManager()->AddEvent(new TestEvent());
	}

	//------------------------------------------------------------------------
	// Sample Sound.
	//------------------------------------------------------------------------
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_B, true))
	{
		App::PlaySound(".\\TestData\\Test.wav");
	}
}

//------------------------------------------------------------------------
// Add your display calls here (DrawLine,Print, DrawSprite.) 
// See App.h 
//------------------------------------------------------------------------
void Render()
{	

	map->Draw(world->GetActiveCamera());

	//------------------------------------------------------------------------
	// Example Sprite Code....
	//testSprite->Draw();
	world->Draw();
	//------------------------------------------------------------------------

	//------------------------------------------------------------------------
	// Example Text.
	//------------------------------------------------------------------------
	App::Print(100, 100, ("PlayerX: " + std::to_string(((Actor*)(obj))->GetActorLocation().x)).c_str());
	App::Print(100, 150, ("PlayerCamX: " + std::to_string(((Actor*)(obj))->GetComponentOfClass<CCamera>()->GetCameraOrigin().x)).c_str());

	
}
//------------------------------------------------------------------------
// Add your shutdown code here. Called when the APP_QUIT_KEY is pressed.
// Just before the app exits.
//------------------------------------------------------------------------
void Shutdown()
{	
	delete GameEngine;

	bool shutdown = true;

}