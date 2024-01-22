#pragma once
/*
*	 Engine - Tile Movement Component
*	A movement component that take in input at attempts to move on a tilemap
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