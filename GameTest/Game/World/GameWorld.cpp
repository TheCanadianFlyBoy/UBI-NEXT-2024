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

PlayerController* LocalController;
AIController* EnemyController;

CRigidBody* Hull;



GameWorld::GameWorld() : World()
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



	//Setup enemy
	Enemy = CreateEntity<Cruiser>();
	Enemy->SetActorLocation(Vector2(2000.f, 220.f));
	Enemy->FireControlComponent->FlipAxis();

	Waves = CreateEntity<WaterRenderer>();
	Waves->SetActorLocation(Vector2(-5000.f, 0.f));


	

	
	State->RegisterShip(Enemy, 1);



}

void GameWorld::OnBegin()
{
	World::OnBegin();

	//UI SETUP
	UIHUDCanvas* Canvas = WorldObjectManager->CreateCanvas<UIHUDCanvas>();
	Canvas->AimPointWidget->SetPlayerController(LocalController);

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



}