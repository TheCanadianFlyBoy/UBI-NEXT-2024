#pragma once
/*
*	CFB Engine - Event
*   A basic archetype for all events in the event system.
*
*/

#include "../Object/Object.h"
#include "../Math/Collision.h"

#include <functional>

class Event
{
    friend class EventManager;

public:
    Event() {};
    virtual ~Event() {}; // = 0?? tODO

    virtual const char* GetEventType() = 0;

protected:
    void SetDelay(float InDelay) { Delay = InDelay; }
    float Delay = 0.0f;
};

class TestEvent : public Event
{
public:
    static const char* GetStaticEventType() { return "TestEvent"; }
    virtual const char* GetEventType() override { return GetStaticEventType(); }
};

class CollisionEvent : public Event
{
public:
    static const char* GetStaticEventType() { return "CollisionEvent"; }
    virtual const char* GetEventType() override { return GetStaticEventType(); }
    
    CollisionEvent(CollisionInfo Info) : OutHit(Info) {};

    CollisionInfo OutHit;

};

class LoadLevelEvent : public Event
{
public:
    static const char* GetStaticEventType() { return "LoadLevelEvent"; }
    virtual const char* GetEventType() override { return GetStaticEventType(); }

    LoadLevelEvent(std::string InWorld) : WorldToLoad(InWorld) {};

    std::string WorldToLoad;
};

