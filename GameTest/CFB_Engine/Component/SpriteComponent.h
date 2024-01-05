#pragma once
/*
*	CFB Engine - Sprite Component
*	Basic sprite component for provided sprite system. Uses transform component as a base to allow for offsets.
*
*
*/

//Super
#include "TransformComponent.h"

class CSimpleSprite;
class Entity;

class CSprite : public CTransform
{
public: 
	//Class Name
	inline virtual const char* GetObjectClassName() override { return GetStaticClassName(); }
	inline static const char* GetStaticClassName() { return "CSprite"; }

	//CONSTRUCTORS
	//Empty sprite component
	CSprite(Entity* InOwner = nullptr) { Owner = InOwner; };
	//Sprite instantiation constructor 
	CSprite(Entity* InOwner, const char* fileName, unsigned int columns = 1U, unsigned int rows = 1U);


	//Draw call
	void Draw();
	

protected:
	std::unique_ptr<CSimpleSprite> Sprite;


};