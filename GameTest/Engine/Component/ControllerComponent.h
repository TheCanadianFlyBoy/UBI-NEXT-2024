#pragma once
/*
*	CFB Engine - Controller Component
*	An archetype component for all controllers in the game
*
*/

#include "Component.h"

class CInput : public Component
{
public:
	//Class Name
	inline virtual const char* GetObjectClassName() override { return GetStaticClassName(); }
	inline static const char* GetStaticClassName() { return "CInput"; }

	CInput(Entity* InEntity) : Component(InEntity) {};


};