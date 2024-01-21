#pragma once
/*
*	CFB Engine - Timer Manager
*	A simple timer manager using pairs of timers with callback functions
*
*/

#include <functional>
#include "../Object/Entity.h"

struct Timer {

	Timer(float InLength, std::function<void()> InFunction) { TimerLength = InLength; CallbackFunction = InFunction; }

	//Timing
	float CurrentTime = 0.f;
	float TimerLength = 1.f;

	//Callback info
	std::function<void()> CallbackFunction;

};


class TimerManager : public Entity
{
	DECLARE_SINGLE(TimerManager);

public:
	

	virtual void Update(float DeltaTime) override;

	//Sets a timer and returns its ID
	int SetTimer(float Length, std::function<void()> Callback, void* Object);

	inline void Flush() { Timers.clear(); }

protected:

	std::vector<std::shared_ptr<Timer>> Timers;

};