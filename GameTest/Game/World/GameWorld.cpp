#include "stdafx.h"
#include "GameWorld.h"
#include "../Environment/Water.h"
#include "../../Engine/Managers/SpriteManager.h"
#include "../Object/Projectile.h"
#include "../Object/Ship.h"
#include "../Component/FireControlComponent.h"
#include "../GameUI.h"
#include "TurnBasedState.h"

WaterRenderer* Waves;


Ship* Enemy;
Actor* MouseActor;

CRigidBody* Hull;
CRigidBody* MouseBody;


GameWorld::GameWorld(EngineCore* Engine) : World(Engine)
{
	//Setup state
	

	//Setup Player
	PlayerShip = CreateEntity<Destroyer>();
	PlayerShip->SetActorLocation(PlayerShipLocation);

	//Camera
	CCamera* Cam = PlayerShip->CreateComponent<CCamera>();
	Cam->SetCameraLag(0.09f);
	SetActiveCamera(Cam);

	//Setup enemy
	Enemy = CreateEntity<Destroyer>();
	Enemy->SetActorLocation(Vector2(5000.f, 220.f));

	Waves = CreateEntity<WaterRenderer>();
	Waves->SetActorLocation(Vector2(-5000.f, 0.f));

	UIAimPoint* AimPoint = WorldObjectManager->CreateCanvas<UICanvas>()->AddWidget<UIAimPoint>();
	AimPoint->SetCurrentShip(PlayerShip);


	MouseActor = CreateEntity<Actor>();
	CRigidBody* Body = MouseActor->CreateComponent<CRigidBody>();
	Body->MakeCollisionCircle(Vector2(0.f, 0.f), 20.f);
	Body->SetGravityScale(0.f);

	MouseBody = Body;



}

void GameWorld::Update(float DeltaTime)
{
	//Super
	World::Update(DeltaTime);

	//PlayerShip->AddActorLocation(Vector2(App::GetController().GetLeftThumbStickX(), App::GetController().GetLeftThumbStickY()));

	Waves->Update(DeltaTime);

	Debug::PrintLine("projectiles:" + std::to_string(WorldObjectManager->GetEntityInstanceCount("Projectile")));
	Debug::PrintLine("particles:" + std::to_string(WorldObjectManager->GetEntityInstanceCount("ParticleSprite")));

}

void GameWorld::Render()
{
	World::Render();

	Waves->Render(ActiveCamera);

	std::string text = "Player:" + std::to_string(PlayerShip->GetActorLocation().x) + "," + std::to_string(PlayerShip->GetActorLocation().y);

	Debug::DrawLineInWorld(Vector2(200.f), PlayerShip->GetActorLocation(), ActiveCamera, Color3(1.f, 0.f, 1.f));

	App::Print(20.f, 20.f, text.c_str());

	MouseActor->SetActorLocation(ENGINE->GetMouseScreenPosition() + ActiveCamera->GetCameraOrigin());

	

	Debug::DrawRectangleInWorld(Enemy->GetActorLocation() + Vector2(0.f, 50.f), Vector2(Enemy->GetComponentOfClass<CHealth>()->GetHealth(), 6.f), ActiveCamera, Color3(0.f, 1.f, 0.f));
	Debug::DrawCircleInWorld(PlayerShip->GetActorLocation() + PlayerShip->FireControlComponent->GetAimVector(), 12.f, GetActiveCamera(), 5);

}