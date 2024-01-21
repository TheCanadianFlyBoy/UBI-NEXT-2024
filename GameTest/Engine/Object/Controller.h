#pragma once
/*
*	CFB Engine - Controller
*	The archetype for all controllers, AI and Player, in the engine
*
*/

#include "Actor.h"

class World;

class Controller : public Actor
{
public:
	//Class Name
	inline virtual const char* GetObjectClassName() override { return GetStaticClassName(); }
	inline static const char* GetStaticClassName() { return "Controller"; }

	//Default Constructor with optional args
	Controller(World* InWorld = nullptr, Actor* InActor = nullptr) : Actor(InWorld) { if (InActor) Possess(InActor); };

	//Update
	virtual void Update(float DeltaTime) { Entity::Update(DeltaTime); };


public: // Methods

		//Possession
	//Possess
	void Possess(Actor* InActor);
	virtual void OnPossess(Actor* InActor) {};
	//UnPossess
	void UnPossess();
	virtual void OnUnPossess() {};

		//Input Data
	//Setters
	inline void SetInputLeft(Vector2& InVector) { InputLeft = InVector; };
	inline void SetInputRight(Vector2& InVector) { InputRight = InVector; };
	inline void SetControlRotation(float& InRotation) { ControlRotation = InRotation; };
	//Getters
	inline Vector2 GetInputLeft() { return InputLeft; };
	inline Vector2 GetInputRight() { return InputRight; }
	inline float GetControlRotation() { return ControlRotation; };

protected: // Members
	//Controller data
	Vector2 InputLeft = Vector2(0.f);
	Vector2 InputRight = Vector2(0.f);
	float ControlRotation = 0.f;

	//Controlled Actor
	Actor* PossessedActor = nullptr;


};