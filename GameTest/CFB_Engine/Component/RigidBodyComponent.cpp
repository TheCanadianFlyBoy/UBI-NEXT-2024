#include "stdafx.h"
#include "RigidBodyComponent.h"
#include "../Object/Actor.h"

#include "../Math/Collision.h"

void CRigidBody::Update(float DeltaTime)
{
	//Check if we have a transform to snag
	if (Actor* ActorOwner = dynamic_cast<Actor*>(Owner))
	{
		//Ensure we have made a shape
		if (CollisionShape)
		{
			CollisionShape->Position = ActorOwner->GetActorLocation();
		}
	}
}

void CRigidBody::MakeCollisionCircle(Vector2 InOffset, float InRadius)
{
	//Handles transform
	if (Actor* OwnerActor = dynamic_cast<Actor*>(Owner)) InOffset += OwnerActor->GetActorLocation();
	//Reset in case of previous shape
	CollisionShape.reset(nullptr);
	//Create the pointer
	CollisionShape = std::make_unique<CollisionCircle>(InOffset, InRadius);
}

void CRigidBody::MakeCollisionBox(Vector2 InOffset, Vector2 InBounds)
{
	//Handles transform
	if (Actor* OwnerActor = dynamic_cast<Actor*>(Owner)) InOffset += OwnerActor->GetActorLocation();
	//Reset in case of previous shape
	CollisionShape.reset(nullptr);
	//Create the pointer
	CollisionShape = std::make_unique<CollisionBox>(InOffset, InBounds);
}

bool CRigidBody::GetBodyCollision(CRigidBody* Other, CollisionInfo& OutHitInfo)
{
	CollisionPrimitive* ThisShape = GetCollisionShape();
	CollisionPrimitive* OtherShape = Other->GetCollisionShape();

	//Eject if invalid shapes
	if (!ThisShape || !OtherShape) return false;

	//Handle all cases
	//AABB
	if (ThisShape->GetObjectClassName() == "CollisionBox")
	{
		CollisionBox* ThisBox = static_cast<CollisionBox*>(ThisShape);

		if (OtherShape->GetObjectClassName() == "CollisionBox")
		{	//Cast
			CollisionBox* OtherBox = static_cast<CollisionBox*>(OtherShape);
			
			//Call
			return ThisBox->AABBToAABB(*OtherBox);

			
		}
		else if (OtherShape->GetObjectClassName() == "CollisionCircle")
		{	//Cast
			CollisionCircle* OtherCircle = static_cast<CollisionCircle*>(OtherShape);

			//Call
			return ThisBox->CircleToAABB(*OtherCircle);


		}
	}
	else if (ThisShape->GetObjectClassName() == "CollisionCircle")
	{
		CollisionCircle* ThisCircle = static_cast<CollisionCircle*>(ThisShape);

		if (OtherShape->GetObjectClassName() == "CollisionBox")
		{	//Cast
			CollisionBox* OtherBox = static_cast<CollisionBox*>(OtherShape);

			//Call
			return OtherBox->CircleToAABB(*ThisCircle);


		}
		else if (OtherShape->GetObjectClassName() == "CollisionCircle")
		{	//Cast
			CollisionCircle* OtherCircle = static_cast<CollisionCircle*>(OtherShape);

			//Call
			return ThisCircle->CircleToCircle(*OtherCircle);


		}
	}


	return false;
}
