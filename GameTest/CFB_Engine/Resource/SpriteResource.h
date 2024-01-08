#pragma once
/*
*	CFB Engine - Sprite Resource
*	A basic object for storing relevant sprite data.
*
*/

#include <memory>
#include <string>

#include "../Object/Object.h"
#include "../../App/SimpleSprite.h"

class SpriteResource : public Object
{
	//Class Name
	inline virtual const char* GetObjectClassName() override { return GetStaticClassName(); }
	inline static const char* GetStaticClassName() { return "SpriteResource"; }

	SpriteResource() {};
	SpriteResource(std::string InSpriteName, const char* InFileName, unsigned int InColumns = 1, unsigned int InRows = 1);


public: //Methods
	//Naming
	inline const std::string& GetName() { return SpriteName; }

protected: // Members

	std::vector<std::shared_ptr<CSimpleSprite>> SpriteInstances;

	//Object name
	std::string SpriteName = "";

	const char* FileName;
	unsigned int Columns;
	unsigned int Rows;


};