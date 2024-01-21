#include "stdafx.h"
#include "Controller.h"

/// <summary>
/// Handles the possession of a given actor
/// </summary>
/// <param name="InActor"></param>
void Controller::Possess(Actor* InActor)
{
	if (PossessedActor) UnPossess();

	//Save reference
	PossessedActor = InActor;

	//Call on possessed
	OnPossess(InActor);

}

/// <summary>
/// Handles the removal of the possessed actor
/// </summary>
/// <param name="InActor"></param>
void Controller::UnPossess()
{
	//Call OnUnPossess FIRST
	OnUnPossess();

}
