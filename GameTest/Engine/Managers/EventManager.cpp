#include "stdafx.h"
#include "EventManager.h"
#include "../World/World.h"
#include "../State/GameState.h"
#include "../Engine.h"


void EventManager::ProcessEvents(float DeltaTime)
{
    //If empty, return
    if (EventQueue.empty())
        return;

    while (EventQueue.empty() == false)
    {
        // Remove it from the queue.
        std::shared_ptr<Event> CurrentEvent = EventQueue.front();

        // Send it to the game.
        ENGINE->GetCurrentWorld()->GetWorldGameState()->OnEvent(CurrentEvent, DeltaTime);

        // Delete the event.
        EventQueue.pop();
    }
}
