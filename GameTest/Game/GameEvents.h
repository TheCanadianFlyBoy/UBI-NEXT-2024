#pragma once
/*
*	ANGRY SHIPS - Events
*	Game Based Events
*
*/

#include "../Engine/Event/Event.h"


class SpawnEvent : public Event
{
public:
	static const char* GetStaticEventType() { return "SpawnEvent"; }
	virtual const char* GetEventType() override { return GetStaticEventType(); }

	SpawnEvent(std::string InName, int InPlayerID) : Event()
	{
		Name = InName;
		PlayerID = InPlayerID;
	}

	std::string Name = "";
	int PlayerID = 0;


};