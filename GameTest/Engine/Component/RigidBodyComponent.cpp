#include "stdafx.h"
#include "../Engine.h"
#include "RigidBodyComponent.h"
#include "../Object/Actor.h"
#include "../Utility/Debug.h"
#include "../Math/Collision.h"
#include "CameraComponent.h"

CRigidBody::CRigidBody(Entity* InEntity) : CTransform(InEntity)
{
	if (Actor* ActorOwner = dynamic_cast<Actor*>(Owner)) {
		ActorOwner->GetWorld()->RegisterCollisionEntity(this);
	}
}

CRigidBody::~CRigidBody()
{
	
}

void CRigidBody::Update(float DeltaTime)
{
	

}

void CRigidBody::LateUpdate(float DeltaTime)
{
	//Move in tree
	ENGINE->GetCurrentWorld()->UnRegisterCollisionEntity(this);
	ENGINE->GetCurrentWorld()->RegisterCollisionEntity(this);

	//Clean overlaps
	OverlappingBodies.erase(std::remove_if(OverlappingBodies.begin(), OverlappingBodies.end(), [](CRigidBody* val) { return !val->Active; }), OverlappingBodies.end());

}

/// <summary>
/// Calculate physics
/// </summary>
void CRigidBody::FixedUpdate()
{
	float DeltaTime = FIXED_UPDATE_FREQUENCY;

	//Check if we have a transform to snag
	if (Actor* ActorOwner = dynamic_cast<Actor*>(Owner))
	{
		//Ensure we have made a shape
		if (CollisionShape)
		{
			CollisionShape->Position = ActorOwner->GetActorLocation() + Offset;
			//CollisionShape->Rotation
		}


		//Do Rotation
		AngularVelocity = MathOps::FLerp(AngularVelocity, 0.f, DeltaTime * AngularDamping);

		//Do gravity
		Velocity += Vector2(0.f, -GravityScale * DeltaTime * 0.01f * Mass);

		//Lerp toward
		AngularVelocity += MathOps::FSign(Velocity.y) * DeltaTime * 0.0001f;

		//Do physics 'sim'
		ActorOwner->AddActorLocation(Velocity);
		//ActorOwner->AddActorRotation(AngularVelocity);

		ApplyBuoyancy(DeltaTime);

		//Damping(DeltaTime);

	}
}

void CRigidBody::Render(CCamera* InCamera)
{
	if (ENGINE_DEBUG_MODE)
	{
		if (CollisionShape)
			CollisionShape->DebugDraw(InCamera, OverlappingBodies.size() > 0 ? Color3(1.f, 0.f, 0.f) : Color3(1.f));

		if (!BuoyancyCircles.empty())
		{
			for (auto& Circle : BuoyancyCircles)
			{
				if (Actor* ActorOwner = dynamic_cast<Actor*>(Owner)) {
					Vector2 DrawPosition = ActorOwner->GetActorLocation();
					//Get if box
					if (CollisionShape->GetObjectClassName() == "CollisionBox") {
						CollisionBox* ThisBox = static_cast<CollisionBox*>(CollisionShape.get());
						DrawPosition = ThisBox->GetMin();
					}

					Debug::DrawCircle(DrawPosition + Circle->Position - InCamera->GetCameraOrigin() , Circle->Radius, 8, Color3(1.f, 1.f, 0.f));
				}
			}
		}

	}
}

void CRigidBody::Shutdown()
{
	CTransform::Shutdown();

	if (Actor* ActorOwner = dynamic_cast<Actor*>(Owner))
	{
		ActorOwner->GetWorld()->UnRegisterCollisionEntity(this);
	}

	Velocity = 0.f;
}

void CRigidBody::OnBegin()
{
	CTransform::OnBegin();

	//Add self to ignore
	AddIgnoredEntity(Owner);

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
	CollisionShape = std::make_unique<CollisionBox>(InOffset, InBounds, true);
}

bool CRigidBody::GetCollision(CRigidBody* Other, CollisionInfo& Info)
{
	//Inactive check
	if (!Other->Active || !Active) return false;

	//Ignore check
	for (auto& ThisEntity : IgnoredEntities)
	{
		//Found an ignoreable
		if (ThisEntity == Other->Owner)
		{
			//Do not need to do anything
			return false;
		}
	}

	//Fill out partial hit info
	Info.ThisActor = dynamic_cast<Actor*>(Owner);
	Info.ThisBody = this;
	Info.OtherActor = dynamic_cast<Actor*>(Other->Owner);
	Info.OtherBody = Other;

	//Get result
	bool Result = GetCollision(*Info.OtherBody->GetCollisionShape(), Info);

	//If hit, do overlapping
	if (Result) 
	{
		//If this is our first hit, send it
		if (!IsOverlappingBody(Info.OtherBody))
			ENGINE->GetCurrentWorld()->GetWorldEventManager()->AddEvent(std::make_shared<CollisionEvent>(Info));
		//Add
		Info.ThisBody->RegisterOverlappingBody(Info.OtherBody);
		Info.OtherBody->RegisterOverlappingBody(Info.ThisBody);
		//If
	}
	else {
		Info.ThisBody->RemoveOverlappingBody(Info.OtherBody);
		Info.OtherBody->RemoveOverlappingBody(Info.ThisBody);
	}

	return Result;

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

			//Call
			return ThisBox->CircleToAABB(*OtherCircle, CollisionLine(Position, Velocity), OutHitInfo);


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
			return OtherBox->CircleToAABB(*ThisCircle, CollisionLine(Position, Velocity), OutHitInfo);


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


/// <summary>
/// Handles buoyancy by using a global hard deck for water surface
/// </summary>
void CRigidBody::SetupBuoyancyCircles()
{
	if (CollisionShape->GetObjectClassName() == "CollisionBox")
	{
		SetupBoxBuoyancy();
	}
	else if (CollisionShape->GetObjectClassName() == "CollisionCircle")
	{
		CollisionCircle* Circle = static_cast<CollisionCircle*>(CollisionShape.get());

		BuoyancyCircles.push_back(std::make_shared<BuoyancyCircle>(Owner, Vector2(0.f), Circle->Radius, 1.f));
	}

}

void CRigidBody::ApplyBuoyancy(float DeltaTime)
{
	if (Actor* OwnerActor = dynamic_cast<Actor*>(Owner)) 
	{
		//Iterate
		for (auto& Circle : BuoyancyCircles)
		{
			//Get bottom
			Vector2 WorldPosition = OwnerActor->GetActorLocation() + Circle->Position;

			if (WorldPosition.y > 220.f) return;

			float CircleBottom = WorldPosition.y - Circle->Radius;
			//Calculate submersion
			//TODO make varied/collision based
			float SubmersionHeight = 220.f - CircleBottom;
			//SubmersionHeight = 

			float DisplacementVolume = PI * Circle->Radius * Circle->Radius - MathOps::CalculateCircleSegment(Circle->Radius, SubmersionHeight);
			DisplacementVolume *= Circle->Adjustment;

			//Get fluid weight
			float FluidWeight = DisplacementVolume * ObjectDensity * GravityScale; //TODO make water body based

			//Calculate force
			float Force = -FluidWeight * 0.0001f;
			assert(!isnan(Force));

			if (Velocity.y > 0.f)
				Force -= Velocity.y * Velocity.y; //todo damping

			Velocity -= Vector2(0.f, Force * DeltaTime * 0.001f);



		}
	};



}

void CRigidBody::Damping(float DeltaTime)
{
	Velocity.x = MathOps::FLerp(Velocity.x, 0, DeltaTime * VelocityDamping);
	Velocity.y = MathOps::FLerp(Velocity.y, 0, DeltaTime * VelocityDamping);

}

/// <summary>
/// Registers another body as overlapping for debouncing purposes
/// </summary>
/// <param name="InBody">Overlapping body</param>
void CRigidBody::RegisterOverlappingBody(CRigidBody* InBody)
{
	//Check if it's already contained before we start
	if (!IsOverlappingBody(InBody))
	{
		OverlappingBodies.push_back(InBody);
	}
}

void CRigidBody::RemoveOverlappingBody(CRigidBody* InBody)
{
	//Iterator
	std::vector<CRigidBody*>::iterator itr;

	itr = OverlappingBodies.begin();

	while (itr != OverlappingBodies.end())
	{
		if (*itr == InBody)
		{
			OverlappingBodies.erase(itr);
			return;
		}
		else 
		{
			itr++;
		}

	}
}

/// <summary>
/// Finds if a given body is already overlapping
/// </summary>
/// <param name="InBody">Overlapping body to search</param>
bool CRigidBody::IsOverlappingBody(CRigidBody* InBody)
{
	//Iterate
	for (auto& Body : OverlappingBodies)
	{
		if (Body == InBody) return true;
	}

	return false;
}

/// <summary>
/// Creates the appropriate number of circles in the box
/// </summary>
void CRigidBody::SetupBoxBuoyancy()
{
	//Get box reference
	CollisionBox* Box= static_cast<CollisionBox*>(CollisionShape.get());

	//Calculate how many circles can fit
	int MaxXSpheres = std::max<int>(int(Box->Bounds.x / (BuoyancyCircleRadius * 2.f)), 1);
	int MaxYSpheres = std::max<int>(int(Box->Bounds.y / (BuoyancyCircleRadius * 2.f)), 1);

	for (int i = 0; i < MaxXSpheres; i++)
	{
		for (int j = 0; j < MaxYSpheres; j++)
		{
			//Setup coordinates
			Vector2 Offset = Vector2(BuoyancyCircleRadius) + (Vector2(BuoyancyCircleRadius * 2 * i, BuoyancyCircleRadius * 2 * j));

			//Calculate volume
			float BoxVolume = Box->Bounds.x * Box->Bounds.y;
			float CircleVolume = PI * BuoyancyCircleRadius * BuoyancyCircleRadius;

			float Adjustment = BoxVolume / CircleVolume;
			
			//Create
			BuoyancyCircles.push_back(std::make_shared<BuoyancyCircle>(Owner, Offset, BuoyancyCircleRadius, Adjustment));



		}
	}


}
