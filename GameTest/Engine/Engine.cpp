#include "stdafx.h"
#include "Engine.h"
#include "Managers/SpriteManager.h"
#include "Utility/EngineProfiler.h"

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
	FixedUpdateTimer += DeltaTime * 0.01f;
	

	//Update global UI first
	for (auto& Canvas : GlobalCanvases)
	{
		Canvas->Update(DeltaTime);
	}

	//Update world
	if (CurrentWorld)
	{
		CurrentWorld->Update(DeltaTime);

		if (FixedUpdateTimer > FIXED_UPDATE_FREQUENCY)
		{
			CurrentWorld->FixedUpdate();
		}

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

	if (ENGINE_DEBUG_MODE)
	{
		EngineProfiler::GetInstance()->Render();
	}
}

/// <summary>
/// Handle safe closure of the game
/// </summary>
void EngineCore::Shutdown()
{
	if (CurrentWorld) CurrentWorld->Shutdown();
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

/// <summary>
/// Helper function to get the mouse position in vector format
/// </summary>
/// <returns></returns>
Vector2 EngineCore::GetMouseScreenPosition()
{
	float x; float y;
	
	App::GetMousePos(x, y);

	return Vector2(x, y);
}

/// <summary>
/// Helper function that gets the mouse in vector format, in world context
/// </summary>
/// <returns></returns>
Vector2 EngineCore::GetMouseWorldPosition()
{
	//If camera, do origin shift
	if (GetActiveWorldCamera()) 
		return GetMouseScreenPosition() + GetActiveWorldCamera()->GetCameraOrigin();
	//Else
	return GetMouseScreenPosition();
}
