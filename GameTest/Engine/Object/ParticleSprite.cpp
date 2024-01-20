#include "stdafx.h"
#include "ParticleSprite.h"
#include "../Component/SpriteComponent.h"

/// <summary>
/// Creates the standard particle components
/// </summary>
/// <param name="InWorld"></param>
ParticleSprite::ParticleSprite(World* InWorld) : Actor(InWorld)
{ 
	//Set auto deactivation to true
	AutoDeactivates = true; 

	//Set default lifetime to 3 seconds
	LifetimeMax = 3.f;

	//Create sprite component
	SpriteComponent = CreateComponent<CSprite>();

}

/// <summary>
/// Resets animation
/// </summary>
void ParticleSprite::OnBegin()
{
	//Super
	Actor::OnBegin();

	//Nullguard
	if (SpriteComponent)
	{
		SpriteComponent->SetFrame(0);
	}

}
