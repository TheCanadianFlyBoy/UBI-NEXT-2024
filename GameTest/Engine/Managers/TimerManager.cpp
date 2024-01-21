#include "stdafx.h"
#include "TimerManager.h"

/// <summary>
/// Increment timers and issue callbacks
/// </summary>
/// <param name="DeltaTime"></param>
void TimerManager::Update(float DeltaTime)
{
	//Iterate
	for (auto& ThisTimer : Timers)
	{
		//Increment
		ThisTimer->CurrentTime += DeltaTime * 0.01f;
		//Check if we've elapsed time
		if (ThisTimer->CurrentTime > ThisTimer->TimerLength)
		{
			//Issue callback
			ThisTimer->CallbackFunction();
		}
	}

	//Erase
	std::_Erase_remove_if(Timers, [](std::shared_ptr<Timer> Ptr) { return Ptr->CurrentTime > Ptr->TimerLength; });
}

/// <summary>
/// Push a new timer
/// </summary>
/// <param name="Length"></param>
/// <param name="Callback"></param>
/// <param name="Object"></param>
/// <returns></returns>
int TimerManager::SetTimer(float Length, std::function<void()> Callback, void* Object)
{
	//Push
	Timers.push_back(std::make_shared<Timer>( Length, Callback ));

	return Timers.size() - 1;
}
