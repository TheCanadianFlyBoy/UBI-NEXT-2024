#include "stdafx.h"
#include "CameraComponent.h"
#include "../Object/Actor.h"
#include "../Math/MathOps.h"
#include "../Object/Entity.h"

void CCamera::Update(float DeltaTime)
{

	//If we have an owner attached
	if (Owner && Owner->GetComponentOfClass<CTransform>())
	{
		//Get the transform
		CTransform* OwnerTransform = Owner->GetComponentOfClass<CTransform>();

		//Setup default target: self
		Vector2 Target = OwnerTransform->GetPosition() - Dimensions / 2 + GetPosition();

		//Check if we have another target
		if (TargetActor && TargetActor->Active)
		{
			Target = TargetActor->GetActorLocation() - Dimensions / 2 + GetPosition();
		}

		//Lerp toward the target position
		Origin = MathOps::VectorLerp(Origin, Target, DeltaTime * CameraLag * CameraLag);

		//Clamp
		if (bCameraIsBound) {
			if (fabsf(Origin.x - Target.x) > CameraMaxDistance) Origin.x = Target.x - (MathOps::FSign(Target.x - Origin.x) * CameraMaxDistance);
			if (fabsf(Origin.y - Target.y) > CameraMaxDistance) Origin.y = Target.y - (MathOps::FSign(Target.y - Origin.y) * CameraMaxDistance);
		}

	}
}

