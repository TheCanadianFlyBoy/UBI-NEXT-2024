#include "stdafx.h"
//Self
#include "TileMovementComponent.h"
//Entity
#include "../Object/Entity.h"
#include "../Object/Actor.h"
//Tilemap
#include "../World/Tilemap.h"
//App
#include "../App/app.h"

void CTileMovement::MoveOnTilemap(Vector2 Input, Tilemap* Map, float DeltaTime)
{
	Actor* ActorOwner = dynamic_cast<Actor*>(Owner);

	//Check if no inputs
	if (Input.LengthSquared() == 0.0f || !ActorOwner) return;

	//Check new positions
	float XComponent = Input.x * WalkSpeed * DeltaTime;
	float YComponent = Input.y * WalkSpeed * DeltaTime;

	Vector2 Position = ActorOwner->GetActorLocation();

	float XCost = (float)Map->GetTileCostFromWorldPosition(Position + Vector2(XComponent, 0));
	float YCost = (float)Map->GetTileCostFromWorldPosition(Position + Vector2(0, YComponent));

	Vector2 ResultantVector;
	ResultantVector.x = XCost != -1 ? Input.x : 0;
	ResultantVector.y = YCost != -1 ? Input.y : 0;

	ActorOwner->AddActorLocation(ResultantVector * WalkSpeed * DeltaTime);


}
