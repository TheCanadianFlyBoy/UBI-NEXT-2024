#include "stdafx.h"
#include "GameWorld.h"
#include "../Environment/Water.h"
#include "../../Engine/Managers/SpriteManager.h"
#include "../Object/Projectile.h"

WaterRenderer* Waves;

Actor* MouseActor;

CRigidBody* Hull;
CRigidBody* MouseBody;

GameWorld::GameWorld(EngineCore* Engine) : World(Engine)
{
	//Setup Player
	PlayerShip = CreateEntity<Actor>();
	PlayerShip->SetActorLocation(PlayerShipLocation);

	CSprite* Sprite = PlayerShip->CreateComponent<CSprite>();
	Sprite->SetSprite("Destroyer");
	Sprite->SetPosition(Vector2(5, 16.f));

	
	Vector2 g = Engine->GetSpriteManager()->GetSpriteHeight("DestroyerHull");

	CRigidBody* Body = PlayerShip->CreateComponent<CRigidBody>();
	Hull = Body;

	Vector2 HullDimensions = SpriteManager::GetInstance()->GetSpriteDimensions("DestroyerHull");

	Body->MakeCollisionBox(PlayerShip->GetActorLocation(), HullDimensions - Vector2(0.f, HullDimensions.y /2) );
	Body->SetBuoyancyCircleRadius(8);
	Body->SetMass(1.f);
	//Body->SetGravityScale(0.f);
	Body->SetupBuoyancyCircles();

	Waves = CreateEntity<WaterRenderer>();
	Waves->SetActorLocation(Vector2(-6000.f, 0.f));

	CCamera* Cam = PlayerShip->CreateComponent<CCamera>();
	SetActiveCamera(Cam);


	MouseActor = CreateEntity<Actor>();
	Body = MouseActor->CreateComponent<CRigidBody>();
	Body->MakeCollisionCircle(Vector2(0.f, 0.f), 20.f);
	Body->SetGravityScale(0.f);

	MouseBody = Body;


}

void GameWorld::FireCannon()
{

}

void GameWorld::Update(float DeltaTime)
{
	//Super
	World::Update(DeltaTime);

	PlayerShip->AddActorLocation(Vector2(App::GetController().GetLeftThumbStickX(), App::GetController().GetLeftThumbStickY()));

	Waves->Update(DeltaTime);

	CollisionInfo Hit;

	if (Hull->GetCollision(MouseBody, Hit))
	{
		bool g = true;
	}

	if (App::GetController().CheckButton(XINPUT_GAMEPAD_A))
	{
		Vector2 Trajectory = ENGINE->GetMousePosition() + ActiveCamera->GetCameraOrigin() -  PlayerShip->GetActorLocation();

		Projectile* NewProjectile = CreateEntity<Projectile>();
		//NewProjectile->SetActorRotation(PI / 4);
		NewProjectile->SetActorLocation(PlayerShip->GetActorLocation() + Trajectory.GetNormalized() * 8.f);
		NewProjectile->ProjectileBody->SetVelocity(Vector2(Trajectory.GetNormalized() * -(NewProjectile->ProjectileSpeed)));
		NewProjectile->ProjectileBody->SetGravityScale(9.8f);
		NewProjectile->Owner = PlayerShip;
	}


}

void GameWorld::Render()
{
	World::Render();

	Waves->Render(ActiveCamera);

	std::string text = "Player:" + std::to_string(PlayerShip->GetActorLocation().x) + "," + std::to_string(PlayerShip->GetActorLocation().y);

	Debug::DrawLineInWorld(Vector2(200.f), PlayerShip->GetActorLocation(), ActiveCamera, Color3(1.f, 0.f, 1.f));

	App::Print(20.f, 20.f, text.c_str());

	MouseActor->SetActorLocation(ENGINE->GetMousePosition() + ActiveCamera->GetCameraOrigin());

}