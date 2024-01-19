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
#include "CFB_Engine/Common.h"

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

	ENGINE->LoadWorld(ENGINE->CreateWorld<World>());
	
	UICanvas* TestCanvas = EngineCore::GetInstance()->CreateGlobalCanvas<UICanvas>();

	UIText* TestText = ENGINE->CreateGlobalWidget<UIText>(TestCanvas);
	TestText->SetPosition(Vector2(500.f));
	TestText->SetText("TITLE");

	TestText2 = ENGINE->CreateGlobalWidget<UIButton>(TestCanvas);
	TestText2->SetPosition(Vector2(500.f, 200.f));
	TestText2->SetText("Box");
	TestText2->SetDimensions(Vector2(300, 100));
	TestText2->SetColor(Color3(1.f, 0.f, 0.f));

	Player = ENGINE->GetCurrentWorld()->CreateEntity<Actor>();
	Player->SetActorLocation(Vector2(300.f));
	Body = Player->CreateComponent<CRigidBody>();
	Body->MakeCollisionCircle(Vector2(0.f), 50.f);
	





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
