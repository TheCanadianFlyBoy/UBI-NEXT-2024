#pragma once
/*
*	ANGRY SHIPS - Health Component
*	Component to store health data and call relevant instruction
*
*/

#include "../../Engine/Common.h"

class CHealth : public Component
{
public:
	//Class Name
	inline virtual const char* GetObjectClassName() override { return GetStaticClassName(); }
	inline static const char* GetStaticClassName() { return "CHealth"; }

	CHealth(Entity* InEntity, float InHealth = 100.f) : Component(InEntity), Health(InHealth), MaxHealth(InHealth) {}

	//Health Setters
	inline void SetHealth(float InHealth) { Health = InHealth; };
	inline void SetMaxHealth(float InHealth) { MaxHealth = InHealth; }
	inline void ConfigureHealth(float InHealth) { Health = InHealth; MaxHealth = InHealth; }

	//Health Getters
	inline float GetHealth() { return Health; }
	inline float GetMaxHealth() { return MaxHealth; }
	inline bool Alive() { return Health > 0.f; }

	//Functionality
	inline void Heal(float InHealth) { Health = std::min<float>(Health + InHealth, 100.f); }
	inline void TakeDamage(float InDamage) { Health -= InDamage; }


protected:

	float Health = 100.f;
	float MaxHealth = 100.f;


};