#include "stdafx.h"
#include "SpriteResource.h"

/// <summary>
/// Creates a sprite resource and sprite in a single line.
/// </summary>
/// <param name="FileName">Path to texture</param>
/// <param name="Columns">Number of frame columns</param>
/// <param name="Rows">Number of frame rows</param>
SpriteResource::SpriteResource(std::string InSpriteName, const char* FileName, unsigned int Columns, unsigned int Rows) :
	SpriteName(InSpriteName)
{
	//Create the sprite resource
	//Sprite = new CSimpleSprite(FileName, Columns, Rows);

}
