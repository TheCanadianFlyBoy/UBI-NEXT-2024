#pragma once
/*
*	CFB Engine - Component
*	The archetype for all components in within the ECS.
*
*/

//Parent
#include "Component.h"
//Math
#include "../Math/Vector2.h"

//Forward declaration
class Tilemap;

class CTileMovement : public Component
{
public:
	//Class Name
	inline virtual const char* GetObjectClassName() override { return GetStaticClassName(); }
	inline static const char* GetStaticClassName() { return "CTileMovement"; }

	//Constructor
	CTileMovement(Entity* InEntity = nullptr) : Component(InEntity) { }

	//Movement
	virtual void MoveOnTilemap(Vector2 Input, Tilemap* Map, float DeltaTime);

public: //Members
	float WalkSpeed = 0.1f;


};