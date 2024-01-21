#include "stdafx.h"
#include "Engine.h"
#include "Managers/SpriteManager.h"
#include "Utility/EngineProfiler.h"
#include "Managers/TimerManager.h"

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

	//Do Event Processing
	EventManager::GetInstance()->ProcessEvents(DeltaTime);

	//Handle Timers
	TimerManager::GetInstance()->Update(DeltaTime);

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


void EngineCore::LoadWorld(std::shared_ptr<World> World)
{
	if (CurrentWorld) {
		CurrentWorld->Shutdown();
		EventManager::GetInstance()->AddEvent(std::make_shared<ScheduledLevelDeletion>(CurrentWorld));
	}

	CurrentWorld = World;
	World->OnBegin();
}



/// <summary>
/// Deletes a given world
/// </summary>
/// <param name="InWorld">World to delete</param>
void EngineCore::DeleteWorld(std::shared_ptr<World> World)
{

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
