#include "stdafx.h"
#include "EventManager.h"
#include "../World/World.h"
#include "../State/GameState.h"

/// <summary>
/// Deconstructor with event queue deletion
/// </summary>
EventManager::~EventManager()
{
    while (!EventQueue.empty()) 
    {
        //Grab front
        Event* CurrentEvent = EventQueue.front();
        //Delete
        delete CurrentEvent;
        //Pop
        EventQueue.pop();
    }

}

void EventManager::ProcessEvents(float DeltaTime)
{
    //If empty, return
    if (EventQueue.empty())
        return;

    while (EventQueue.empty() == false)
    {
        // Remove it from the queue.
        Event* CurrentEvent = EventQueue.front();
        EventQueue.pop();

        // Send it to the game.
        ThisWorld->GetWorldGameState()->OnEvent(CurrentEvent, DeltaTime);

        // Delete the event.
        delete CurrentEvent;
    }
}
