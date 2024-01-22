#pragma once
/*
*	CFB Engine - Event
*   A basic archetype for all events in the event system.
*
*/

#include "../Object/Object.h"
#include "../Math/Collision.h"

#include <functional>

class World;

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

class NewLevelEvent : public Event
{
public:
    static const char* GetStaticEventType() { return "NewLevelEvent"; }
    virtual const char* GetEventType() override { return GetStaticEventType(); }
    
    NewLevelEvent() : Event() {};

};

class ScheduledLevelDeletion : public Event
{
public:
    static const char* GetStaticEventType() { return "ScheduledLevelDeletion"; }
    virtual const char* GetEventType() override { return GetStaticEventType(); }

    ScheduledLevelDeletion(std::shared_ptr<World> InWorld = nullptr) : Event()  {};

    std::shared_ptr<World> WorldPointer;

};

class LoadLevelEvent : public Event
{
public:
    static const char* GetStaticEventType() { return "LoadLevelEvent"; }
    virtual const char* GetEventType() override { return GetStaticEventType(); }

    LoadLevelEvent(std::shared_ptr<World> InWorld) : WorldToLoad(InWorld) {};

    std::shared_ptr<World> WorldToLoad;
};

class OpenPauseCanvas : public Event
{
public:
    static const char* GetStaticEventType() { return "OpenPauseCanvas"; }
    virtual const char* GetEventType() override { return GetStaticEventType(); }

    OpenPauseCanvas() {};

};

class ClosePauseCanvas : public Event
{
public:
    static const char* GetStaticEventType() { return "ClosePauseCanvas"; }
    virtual const char* GetEventType() override { return GetStaticEventType(); }

    ClosePauseCanvas() {};

};