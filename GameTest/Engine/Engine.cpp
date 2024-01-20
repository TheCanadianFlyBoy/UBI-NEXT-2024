#include "stdafx.h"
#include "Engine.h"
#include "Managers/SpriteManager.h"

/// <summary>
/// Instantiates all the managers for the engine
/// </summary>
void EngineCore::Initialize()
{
}

/// <summary>
/// 
/// </summary>
/// <param name="DeltaTime"></param>
void EngineCore::Update(float DeltaTime)
{
	//Update global UI first
	for (auto& Canvas : GlobalCanvases)
	{
		Canvas->Update(DeltaTime);
	}

	//Update world
	if (CurrentWorld)
	{
		CurrentWorld->Update(DeltaTime);
	}
}

void EngineCore::LateUpdate(float DeltaTime)
{
	//Update global UI first
	for (auto& Canvas : GlobalCanvases)
	{
		Canvas->LateUpdate(DeltaTime);
	}

	//Update world
	if (CurrentWorld)
	{
		CurrentWorld->LateUpdate(DeltaTime);
	}
}

void EngineCore::Render()
{
	//Render global UI first
	for (auto& Canvas : GlobalCanvases)
	{
		Canvas->Render();
	}

	//Now we render the world
	if (CurrentWorld)
	{
		CurrentWorld->Render();
	}
}

void EngineCore::LoadWorld(World* InWorld)
{
	//TODO handle shutdown of world
	if (CurrentWorld)
		CurrentWorld->Shutdown();

	//Load new world
	CurrentWorld = InWorld;
	CurrentWorld->OnBegin();
}

/// <summary>
/// Deletes a given world
/// </summary>
/// <param name="InWorld">World to delete</param>
void EngineCore::DeleteWorld(World* InWorld)
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

Vector2 EngineCore::GetMousePosition()
{
	float x; float y;
	
	App::GetMousePos(x, y);

	return Vector2(x, y);
}
