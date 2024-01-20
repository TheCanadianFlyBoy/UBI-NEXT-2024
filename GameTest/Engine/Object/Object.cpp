#include "stdafx.h"
#include "Object.h"


void Object::OnBegin()
{
	//Reset flags
	Active = true;
	CurrentLifetime = 0.f;
}

void Object::LateUpdate(float DeltaTime)
{
	//Do auto lifetime
	if (AutoDeactivates && Active) 
	{
		//Convert to seconds
		CurrentLifetime += DeltaTime * 0.001f;

		//Get active
		Active = CurrentLifetime < LifetimeMax;

		//Shutdown if inactive
		if (!Active) Shutdown();

	}
	
}