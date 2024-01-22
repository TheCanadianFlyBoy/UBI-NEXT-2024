#pragma once
/*
*	 Engine - Event Manager
*	Handles incoming events and processes them.
*
*/

#include <queue>
#include "../Object/Entity.h"


class Event;
class World;

class EventManager
{
    DECLARE_SINGLE(EventManager);

public: //Methods

    //Constructor - Requires pointer to game
    //EventManager(World* InWorld) : Entity(InWorld) {}; //TODO GameState
    //~EventManager();

    //Queue Handling
    inline void AddEvent(std::shared_ptr<Event> InEvent) { EventQueue.push(InEvent); };
    void ProcessEvents(float DeltaTime);

    void FlushEvents(float DeltaTime);

protected: //Variables
    std::queue<std::shared_ptr<Event>> EventQueue; //TODO make shared
    //TODO state

};