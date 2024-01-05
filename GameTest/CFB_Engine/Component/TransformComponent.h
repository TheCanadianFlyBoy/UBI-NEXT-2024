#pragma once
/*
*	CFB Engine - Transform Component
*	Basic transform (positon, rotation) component.
*
*
*/

#include "Component.h"
#include "../Math/Vector2.h"

class CTransform : public Component
{
public:
	//Constructor with optional args
	CTransform(Entity* InEntity = nullptr, Vector2 InPosition = {0.f,0.f}, float InRotation = 0.f) : Component(InEntity), Position(InPosition), Rotation(InRotation) {};

	//Class Name
	inline virtual const char* GetObjectClassName() override { return GetStaticClassName(); }
	inline static const char* GetStaticClassName() { return "CTransform"; }

	//Values
	Vector2 Position = {0.f,0.f};
	float Rotation = 0.f;

public: //Methods
	//Math
	///Handles addition
	inline void AddPosition(Vector2 &InPosition)				{ Position += InPosition; };
	///Handles straight scalar multiplication
	inline void ScalarMultiplyPosition(float &Multiplier)	{ Position *= Multiplier; };
	///Handles scalar multiplication with separate axes
	inline void ScalarMultiplyPosition(Vector2 &Multipliers) { Position.x *= Multipliers.x; Position.y *= Multipliers.y; };

	//Setters
	inline void SetPosition(Vector2 &InPosition) { Position = InPosition; };
	inline void SetRotation(float &InRotation)	{ Rotation = InRotation; };

	//Getters
	inline Vector2 GetPosition()	{ return Position; };
	inline float GetRotation()		{ return Rotation; };

};