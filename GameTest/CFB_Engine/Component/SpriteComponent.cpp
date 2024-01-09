#include "stdafx.h"
#include "SpriteComponent.h"
#include "../Object/Entity.h"
#include "../World/World.h"
#include "../Managers/SpriteManager.h"
#include "CameraComponent.h"

/// <summary>
/// Standard Constructor that allows auto allocation of sprite
/// </summary>
/// <param name="InOwner">Owning Entity</param>
/// <param name="InSpriteName">Name of Sprite Resource to Use</param>
CSprite::CSprite(Entity* InOwner, std::string InSpriteName)
	: CTransform(InOwner)
{
	InOwner->GetWorld()->GetEngineSpriteManager()->GetSprite(InSpriteName);
}

/// <summary>
/// Handles draw call for sprite
/// </summary>
void CSprite::Draw(CCamera* InCamera)
{
	//Create variables for draw position and rotation
	Vector2 DrawPosition = Position;	//Offset Position
	float DrawRotation = Rotation;		//Offset Rotation

	//Check for a parent transform
	if (CTransform* ParentTransform = Owner->GetComponentOfClass<CTransform>())
	{
		//Set draw position to owner location
		DrawPosition += ParentTransform->GetPosition(); //SUBTRACT CAMERA FROM HERE
		//Set draw rotation to owner rotation
		DrawRotation += ParentTransform->GetRotation();
	}

	//Check for camera
	if (InCamera)
	{
		DrawPosition -= InCamera->GetCameraOrigin();
	}

	//Update position
	UpdateSpriteLocation(DrawPosition, DrawRotation);

	//Draw call
	Sprite->Draw();
}