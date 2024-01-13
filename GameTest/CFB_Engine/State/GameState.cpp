#include "stdafx.h"
#include "GameState.h"
#include "../Event/Event.h"
#include "../World/World.h" //TODO remove
#include "../Object/Actor.h" // ''
#include "../Component/SpriteComponent.h" // ''
#include "../Managers/SpriteManager.h" //''
#include "../Component/AllComponents.h"

/// <summary>
/// Handles current update functionality
/// </summary>
/// <param name="DeltaTime">Time since last frame</param>
void GameState::Update(float DeltaTime)
{
	//Call the update handler
	(this->*CurrentUpdateHandler)(DeltaTime);
}

/// <summary>
/// Allows processing of events with current event handler
/// </summary>
/// <param name="InEvent">Current Event</param>
/// <param name="DeltaTime">Time since last frame</param>
void GameState::OnEvent(Event* InEvent, float DeltaTime)
{
	// Call current event processing
	(this->*CurrentEventHandler)(InEvent, DeltaTime);
}

/// <summary>
/// Handles rendering of GameState owned objects.
/// </summary>
void GameState::Render()
{
	(this->*CurrentRenderHandler)();
}

/// <summary>
/// An overrideable set state function for flexibility
/// </summary>
/// <param name="State">Current state value</param>
void GameState::SetState(int State)
{
	//Set the state value
	CurrentState = State;

	//This would be where state update logic would occur (switch case)
}

void GameState::TestEventHandler(Event* InEvent, float DeltaTime)
{
	if (InEvent->GetEventType() == "TestEvent")
	{
		//Actor* gub = ThisWorld->CreateEntity<Actor>();
		//CSprite* spr = gub->CreateComponent<CSprite>();
		//spr->SetSprite(ThisWorld->GetEngineSpriteManager()->GetSprite("spr_player"));
	}
}
