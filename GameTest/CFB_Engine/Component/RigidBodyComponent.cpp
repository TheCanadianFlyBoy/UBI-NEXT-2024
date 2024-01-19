#include "stdafx.h"
#include "../Engine.h"
#include "RigidBodyComponent.h"
#include "../Object/Actor.h"
#include "../Utility/Debug.h"
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


		//Do gravity
		Velocity += Vector2(0.f, GravityScale * DeltaTime * 0.01f);

		//Do physics 'sim'
		ActorOwner->AddActorLocation(-Velocity);


	}



}

void CRigidBody::Render()
{
	if (ENGINE_DEBUG_MODE)
	{
		if (CollisionShape)
			CollisionShape->DebugDraw();
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

			CollisionInfo Info;

			//Call
			return ThisBox->CircleToAABB(*OtherCircle, CollisionLine(Position, Velocity), Info);


		}
	}
	else if (ThisShape->GetObjectClassName() == "CollisionCircle")
	{
		CollisionCircle* ThisCircle = static_cast<CollisionCircle*>(ThisShape);

		if (OtherShape->GetObjectClassName() == "CollisionBox")
		{	//Cast
			CollisionBox* OtherBox = static_cast<CollisionBox*>(OtherShape);

			CollisionInfo Info; //TODO flip this ?

			//Call
			return OtherBox->CircleToAABB(*ThisCircle, CollisionLine(Position, Velocity), Info);


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

bool CRigidBody::GetCollision(CollisionPrimitive& InCollisionPrimitive, CollisionInfo& OutHitInfo)
{
	CollisionPrimitive* ThisShape = GetCollisionShape();
	CollisionPrimitive* OtherShape = &InCollisionPrimitive;

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

			CollisionInfo Info;

			//Call
			return ThisBox->CircleToAABB(*OtherCircle, CollisionLine(Position, Velocity), Info);


		}
	}
	else if (ThisShape->GetObjectClassName() == "CollisionCircle")
	{
		CollisionCircle* ThisCircle = static_cast<CollisionCircle*>(ThisShape);

		if (OtherShape->GetObjectClassName() == "CollisionBox")
		{	//Cast
			CollisionBox* OtherBox = static_cast<CollisionBox*>(OtherShape);

			CollisionInfo Info; //TODO flip this ?

			//Call
			return OtherBox->CircleToAABB(*ThisCircle, CollisionLine(Position, Velocity), Info);


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
