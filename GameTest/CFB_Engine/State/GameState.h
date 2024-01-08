#pragma once
/*
*	CFB Engine - Entity
*	The archetype for all game states.
*
*/
#include <iostream>

#include "../Object/Entity.h"
#include "../Event/Event.h" //TODO remove

class EventManager;
class World;
class ObjectManager;
//class UI

class GameState : public Entity
{
	//Function pointers to allow for independent state handlers
	typedef void (GameState::* StateRenderFunction) ();
	typedef void (GameState::* StateUpdateFunction) (float DeltaTime);
	typedef void (GameState::* StateEventsFunction) (Event* inEvent, float DeltaTime);

public: //Common

	//Class Name
	inline virtual const char* GetObjectClassName() override { return GetStaticClassName(); }
	inline static const char* GetStaticClassName() { return "GameState"; }

	//Default constructor with optional world pointer //TODO MAKE NON OPTIONAL
	GameState(World* InWorld = nullptr) : Entity(InWorld) {};

public: //Methods

	//Game Loop
	virtual void Update(float DeltaTime);
	virtual void OnEvent(Event* InEvent, float DeltaTime);
	virtual void Render();

	//Internal Reference Modification
	//Event Manager
	inline void SetEventManager(EventManager* InEventManager) { WorldEventManager = InEventManager; };
	inline EventManager* GetEventManager()				      { return WorldEventManager; };

	//Current World
	inline void SetWorld(World* InWorld) { ThisWorld = InWorld; }

protected: // Members
	EventManager* WorldEventManager = nullptr;
	//UI pointer TODO
	//mathops pointer

	//State value
	int CurrentState = 0;
	//State handler
	virtual void SetState(int State);

	//Function pointers
	StateUpdateFunction CurrentUpdateHandler = &GameState::DefaultUpdateHandler;
	StateRenderFunction CurrentRenderHandler = &GameState::DefaultRenderHandler;
	StateEventsFunction CurrentEventHandler  =  &GameState::TestEventHandler;


protected: // Methods
	//Default Handlers!
	void virtual DefaultUpdateHandler(float DeltaTime)	{};
	void virtual DefaultRenderHandler()					{};
	void virtual DefaultEventHandler(Event* InEvent, float DeltaTime) { };

	void virtual TestEventHandler(Event* InEvent, float DeltaTime);

};