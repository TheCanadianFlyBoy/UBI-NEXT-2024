#pragma once
/*
*	CFB Engine - Event
*   A basic archetype for all events in the event system.
*
*/

#include "../Object/Object.h"

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