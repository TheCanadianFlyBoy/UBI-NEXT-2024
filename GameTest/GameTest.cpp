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
//------------------------------------------------------------------------
#include "app\app.h"
//------------------------------------------------------------------------

//------------------------------------------------------------------------
// Eample data....
//------------------------------------------------------------------------

World* world;
CSprite *testSprite;
Entity* obj;
CTransform* transform;
//ObjectManager* objmanager;
SpriteManager* sprmanager;
Engine* GameEngine;

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


	//Create world
	world = GameEngine->CreateWorld<World>();

	UICanvas* canvas = world->GetWorldObjectManager()->CreateCanvas<UICanvas>();
	world->GetWorldObjectManager()->CreateWidget<UIText>(canvas);


	sprmanager = world->GetEngineSpriteManager();

	//Initialize object manager

	//Register sprite
	sprmanager->RegisterNewSprite("spr_player", ".\\TestData\\Test.bmp", 8, 4, 2);
	float speed = 1.0f / 15.0f;
	sprmanager->RegisterAnimation("spr_player", ANIM_BACKWARDS, speed, {0,1,2,3,4,5,6,7});
	sprmanager->RegisterAnimation("spr_player", ANIM_LEFT, speed, { 8,9,10,11,12,13,14,15 });
	sprmanager->RegisterAnimation("spr_player", ANIM_RIGHT, speed, { 16,17,18,19,20,21,22,23 });
	sprmanager->RegisterAnimation("spr_player", ANIM_FORWARDS, speed, { 24,25,26,27,28,29,30,31 });

	//------------------------------------------------------------------------
	//// Example Sprite Code....
	//testSprite = App::CreateSprite(".\\TestData\\Test.bmp", 8, 4);
	//testSprite->SetPosition(400.0f, 400.0f);
	//testSprite->SetScale(1.0f);
	//------------------------------------------------------------------------
	//CFB
	//TEST 1
	obj = world->CreateEntity<Actor>();

	CCamera* cam = obj->CreateComponent<CCamera>();

	world->SetActiveCamera(cam);

	Entity* dummy = world->CreateEntity<Actor>();
	dummy->GetComponentOfClass<CTransform>()->SetPosition(Vector2(500.f));
	dummy->CreateComponent<CSprite>();
	dummy->GetComponentOfClass<CSprite>()->SetSprite(sprmanager->GetSprite("spr_player"));

	transform = obj->GetComponentOfClass<CTransform>();
	transform->SetPosition(Vector2(50.f));

	testSprite = obj->CreateComponent<CSprite>();
	testSprite->SetSprite(sprmanager->GetSprite("spr_player"));
	

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
	if (App::GetController().GetLeftThumbStickX() > 0.5f)
	{
		testSprite->SetAnimation(ANIM_RIGHT);
		if (obj->GetComponentOfClass<CTransform>()) obj->GetComponentOfClass<CTransform>()->AddPosition(Vector2(1.f, 0.f));


		
	}
	if (App::GetController().GetLeftThumbStickX() < -0.5f)
	{
		testSprite->SetAnimation(ANIM_LEFT);
		transform->Position.x -= 1.0f;
	}
    if (App::GetController().GetLeftThumbStickY() > 0.5f)
    {
        testSprite->SetAnimation(ANIM_FORWARDS);
		transform->Position.y += 1.0f;
    }
	if (App::GetController().GetLeftThumbStickY() < -0.5f)
	{
		testSprite->SetAnimation(ANIM_BACKWARDS);
		transform->Position.y -= 1.0f;
	}
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


	//------------------------------------------------------------------------
	// Example Line Drawing.
	//------------------------------------------------------------------------
	//static float a = 0.0f;
	//float r = 1.0f;
	//float g = 1.0f;
	//float b = 1.0f;
	//a += 0.1f;
	//for (int i = 0; i < 20; i++)
	//{
	//
	//	float sx = 200 + sinf(a + i * 0.1f)*60.0f;
	//	float sy = 200 + cosf(a + i * 0.1f)*60.0f;
	//	float ex = 700 - sinf(a + i * 0.1f)*60.0f;
	//	float ey = 700 - cosf(a + i * 0.1f)*60.0f;
	//	g = (float)i / 20.0f;
	//	b = (float)i / 20.0f;
	//	App::DrawLine(sx, sy, ex, ey,r,g,b);
	//}
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