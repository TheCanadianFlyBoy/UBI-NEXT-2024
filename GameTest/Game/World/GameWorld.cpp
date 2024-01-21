#include "stdafx.h"
#include "GameWorld.h"
#include "../Environment/Water.h"
#include "../../Engine/Managers/SpriteManager.h"
#include "../Object/Projectile.h"
#include "../Object/Ship.h"
#include "../Component/FireControlComponent.h"
#include "../GameUI.h"
#include "TurnBasedState.h"
#include "../Object/PlayerController.h"
#include "../Object/AIController.h"
WaterRenderer* Waves;


Ship* Enemy;
Actor* MouseActor;

PlayerController* LocalController;
AIController* EnemyController;

CRigidBody* Hull;
CRigidBody* MouseBody;


GameWorld::GameWorld(EngineCore* Engine) : World(Engine)
{
	//Setup state
	WorldGameState = std::make_unique<TurnBasedGameState>(this);

	TurnBasedGameState *State = (TurnBasedGameState*)WorldGameState.get(); //TODO cleanup

	//Setup player controller
	LocalController = CreateEntity<PlayerController>();
	LocalController->SetActorLocation(PlayerShipLocation);

	CCamera* Cam = LocalController->CreateComponent<CCamera>();
	Cam->SetCameraLag(0.09f);
	SetActiveCamera(Cam);
	// Setup enemy controller
	EnemyController = CreateEntity<AIController>();

	State->RegisterController(LocalController, 0);
	State->RegisterController(EnemyController, 1);

	//Setup Player
	PlayerShip = CreateEntity<Destroyer>();
	PlayerShip->SetActorLocation(PlayerShipLocation);
	State->RegisterShip(PlayerShip, 0);
	LocalController->Possess(PlayerShip);


	Gunboat* PlayerGunboat = CreateEntity<Gunboat>();
	PlayerGunboat->SetActorLocation(PlayerShipLocation - Vector2(400.f, 0.f));
	State->RegisterShip(PlayerGunboat, 0);
	

	//Setup enemy
	Enemy = CreateEntity<Destroyer>();
	Enemy->SetActorLocation(Vector2(2000.f, 220.f));
	Enemy->FireControlComponent->FlipAxis();

	Waves = CreateEntity<WaterRenderer>();
	Waves->SetActorLocation(Vector2(-5000.f, 0.f));


	//UI SETUP
	UIHUDCanvas* Canvas = WorldObjectManager->CreateCanvas<UIHUDCanvas>();
	Canvas->AimPointWidget->SetPlayerController(LocalController);


	MouseActor = CreateEntity<Actor>();
	CRigidBody* Body = MouseActor->CreateComponent<CRigidBody>();
	Body->MakeCollisionCircle(Vector2(0.f, 0.f), 20.f);
	Body->SetGravityScale(0.f);

	MouseBody = Body;

	
	State->RegisterShip(Enemy, 1);



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