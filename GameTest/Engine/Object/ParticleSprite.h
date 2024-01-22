#pragma once
/*
*	 Engine - Particle Sprite
*	A lighweight variation of an Actor that contains a sprite, and auto deactivates
*
*/

#include "Actor.h"
#include "../Component/TransformComponent.h"
#include "../World/World.h"

class CSprite;

class ParticleSprite : public Actor
{
public:
	//Class Name
	inline virtual const char* GetObjectClassName() override { return GetStaticClassName(); }
	inline static const char* GetStaticClassName() { return "ParticleSprite"; }

	//Constructor
	ParticleSprite(World* InWorld);

	virtual void OnBegin() override;

	//Sets lifetime
	inline void SetLifetime(float InLifetime) { LifetimeMax = InLifetime; }

public: //Members

	CSprite* SpriteComponent = nullptr;

};
