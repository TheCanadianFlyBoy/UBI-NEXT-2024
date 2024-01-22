#pragma once
/*
*	 Engine - Sprite Manager
*	Handles the creation and storage of sprites for usage in the game.
* 
*	Utilizes shared pointers to allow pooling of sprite resources. This system has one caveat
*		- Sprites should be created before runtime for ease of usage
*
*/

#include <memory>
#include <string>

#include "../../App/SimpleSprite.h"
#include "../Math/Vector2.h"


class SpriteResource;

class SpriteManager
{
	DECLARE_SINGLE(SpriteManager);
public: //Sprite Manipulation


	//Creates a brand new sprite from the ground up
	void RegisterNewSprite(std::string InSpriteName, const char* FileName = "", unsigned int Columns = 1U, unsigned int Rows = 1U, unsigned int PoolCount = 1U);
	//Requests a sprite of a given name
	std::shared_ptr<CSimpleSprite> GetSprite(std::string InSpriteName, bool AutoInstantiate = true);

	//Wrappers for CSimpleSprite
	//Animation wrappers
	void RegisterAnimation(std::string InSpriteName, unsigned int AnimationID, float AnimationSpeed, const std::vector<int>& Frames);
	//Getter Wrappers
	float GetSpriteHeight(std::string InSpriteName);
	float GetSpriteWidth(std::string InSpriteName);
	Vector2 GetSpriteDimensions(std::string InSpriteName);


protected: //Methods
	//Sprite Management
	int GetAvailableSpriteIndex(std::string InSpriteName);
	//Generates a new sprite from an existing one
	std::shared_ptr<CSimpleSprite> GenerateSprite(std::string InSpriteName);

protected:

	//Vectors of sprites - Uses Shared Ptrs to maintain lifetime and determine if in use
	std::map<std::string, std::vector<std::shared_ptr<CSimpleSprite>>> SpriteResources;

};