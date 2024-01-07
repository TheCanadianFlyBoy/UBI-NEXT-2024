#include "stdafx.h"
#include "SpriteComponent.h"
#include "../Object/Entity.h"


//Sprite Instantiation Constructor
CSprite::CSprite(Entity* InOwner, const char* fileName, unsigned int columns, unsigned int rows)
	: CTransform(Owner)
{
	//Create new unique pointer to sprite
	Sprite = std::unique_ptr<CSimpleSprite>(new CSimpleSprite(fileName, columns, rows));
}

void CSprite::Draw()
{
	//Create variables for draw position and rotation
	Vector2 DrawPosition = Position;	//Offset Position
	float DrawRotation = Rotation;		//Offset Rotation

	//Check for a parent transform
	if (CTransform* ParentTransform = Owner->GetComponentOfClass<CTransform>())
	{
		//Set draw position to owner location
		DrawPosition = ParentTransform->GetPosition(); //SUBTRACT CAMERA FROM HERE
		//Set draw rotation to owner rotation
		DrawRotation = ParentTransform->GetRotation();
	}
	//Update position
	UpdateSpriteLocation(DrawPosition, DrawRotation);

	//Draw call
	Sprite->Draw();
}