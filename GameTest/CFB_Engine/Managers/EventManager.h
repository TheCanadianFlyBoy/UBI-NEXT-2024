#pragma once
/*
*	CFB Engine - Event Manager
*	Handles incoming events and processes them.
*
*/

#include <queue>
#include "../Object/Entity.h"


class Event;
class World;

class EventManager : public Entity
{
public: //Methods

    //Class Name
    inline virtual const char* GetObjectClassName() override { return GetStaticClassName(); }
    inline static const char* GetStaticClassName() { return "EventManager"; }

    //Constructor - Requires pointer to game
    EventManager(World* InWorld) : Entity(InWorld) {}; //TODO GameState
    ~EventManager();

    //Queue Handling
    inline void AddEvent(Event* InEvent) { EventQueue.push(InEvent); };
    void ProcessEvents(float DeltaTime);


protected: //Variables
    std::queue<Event*> EventQueue;
    //TODO state

};