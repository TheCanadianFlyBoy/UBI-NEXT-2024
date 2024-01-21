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
class Controller;
//class UI


class GameState : public Entity
{
	//Function pointers to allow for independent state handlers
	typedef void (GameState::* StateRenderFunction) ();
	typedef void (GameState::* StateUpdateFunction) (float DeltaTime);
	typedef void (GameState::* StateEventsFunction) (std::shared_ptr<Event> inEvent, float DeltaTime);

public: //Common

	//Default constructor with optional world pointer //TODO MAKE NON OPTIONAL
	GameState(World* InWorld = nullptr) : Entity(InWorld) {};

public: //Methods

	//Game Loop
	virtual void Update(float DeltaTime);
	virtual void OnEvent(std::shared_ptr<Event> InEvent, float DeltaTime);
	virtual void Render();

	//Internal Reference Modification

	//Current World
	inline void SetWorld(World* InWorld) { ThisWorld = InWorld; }

	inline bool CanPassControllerInputs() { return bPassInputsToController; }
	inline bool StopControllerInputs() { bPassInputsToController = false; }
	inline bool AllowControllerInputs() { bPassInputsToController = true; }

	inline int GetCurrentState() { return CurrentState; }

	


protected: // Members
	
	//UI pointer TODO
	//mathops pointer

	//State value
	int CurrentState = 0;

	bool bPassInputsToController = true;
	//State handler
	virtual void SetState(int State);

	//Function pointers
	StateUpdateFunction CurrentUpdateHandler = &GameState::DefaultUpdateHandler;
	StateRenderFunction CurrentRenderHandler = &GameState::DefaultRenderHandler;
	StateEventsFunction CurrentEventHandler  =  &GameState::DefaultEventHandler;


protected: // Methods
	//Default Handlers!
	void virtual DefaultUpdateHandler(float DeltaTime)	{};
	void virtual DefaultRenderHandler() {}; 
	void virtual DefaultEventHandler(std::shared_ptr<Event> InEvent, float DeltaTime); // Need to actually implement to allow easy usage of collision events

	void virtual TestEventHandler(std::shared_ptr<Event> InEvent, float DeltaTime);


};