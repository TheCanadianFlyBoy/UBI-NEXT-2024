#include "stdafx.h"
#include "Engine.h"
#include "Managers/SpriteManager.h"

/// <summary>
/// Instantiates all the managers for the engine
/// </summary>
Engine::Engine()
{
	EngineSpriteManager = std::make_unique<SpriteManager>();
}

/// <summary>
/// Deletes a given world
/// </summary>
/// <param name="InWorld">World to delete</param>
void Engine::DeleteWorld(World* InWorld)
{
	//Size check
	if (Worlds.size() > 0)
	{
		//Iterate
		for (int i = 0; i < Worlds.size(); i ++)
		{
			//Get the current world
			World* CurrentWorld = Worlds[i].get();

			//Check if we have a match
			if (CurrentWorld == InWorld)
			{
				//match, remove
				Worlds.erase(Worlds.begin() + i); //TODO erase remove?
			}

		}
	}
}
