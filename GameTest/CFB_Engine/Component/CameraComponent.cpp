#include "stdafx.h"
#include "CameraComponent.h"

#include "../Math/MathOps.h"
#include "../Object/Entity.h"

void CCamera::Update(float DeltaTime)
{

	//If we have an owner attached
	if (Owner && Owner->GetComponentOfClass<CTransform>())
	{
		//Get the transform
		CTransform* OwnerTransform = Owner->GetComponentOfClass<CTransform>();
		//Calculate our target X
		float TargetX = OwnerTransform->GetPosition().x - Dimensions.x / 2 + GetPosition().x;
		float TargetY = OwnerTransform->GetPosition().y - Dimensions.y / 2 + GetPosition().y;

		//Lerp toward the target position
		Origin.x = MathOps::FLerp(Origin.x, TargetX, CameraLag / DeltaTime);
		Origin.y = MathOps::FLerp(Origin.y, TargetY, CameraLag / DeltaTime);

		//Clamp
		if (fabsf(Origin.x - TargetX) > CameraMaxDistance) Origin.x = TargetX - (MathOps::FSign(TargetX - Origin.x) * CameraMaxDistance);
		if (fabsf(Origin.y - TargetY) > CameraMaxDistance) Origin.y = TargetY - (MathOps::FSign(TargetY - Origin.y) * CameraMaxDistance);


	}
}

