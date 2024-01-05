#include "stdafx.h"
#include "SpriteComponent.h"
#include "../../App/SimpleSprite.h"

//Sprite Instantiation Constructor
CSprite::CSprite(Entity* InOwner, const char* fileName, unsigned int columns, unsigned int rows)
	: CTransform(Owner)
{
	//Create new unique pointer to sprite
	Sprite = std::unique_ptr<CSimpleSprite>(new CSimpleSprite(fileName, columns, rows));
}
