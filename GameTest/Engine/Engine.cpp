#include "stdafx.h"
#include "Engine.h"
#include "Managers/SpriteManager.h"
#include "Utility/EngineProfiler.h"
#include "Managers/TimerManager.h"

/// <summary>
/// Originally here for instantiation, deprecated by singleton design
/// </summary>
void EngineCore::Initialize()
{
}

/// <summary>
/// Handles frame by frame updates
/// </summary>
/// <param name="DeltaTime"></param>
void EngineCore::Update(float DeltaTime)
{
	//Increment fixed update timer
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
		//Call update
		CurrentWorld->Update(DeltaTime);
		//If we have ticked over frequency, do fixed update
		if (FixedUpdateTimer > FIXED_UPDATE_FREQUENCY)
		{
			//Primarily physics calcs
			CurrentWorld->FixedUpdate();
			//Reset timer
			FixedUpdateTimer = 0.f;
		}

	}
}

/// <summary>
/// Handle late update
/// </summary>
/// <param name="DeltaTime"></param>
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

/// <summary>
/// Handle draw calls
/// </summary>
void EngineCore::Render()
{
	//Render the world
	if (CurrentWorld)
	{
		CurrentWorld->Render();
	}
	//Render global UI
	for (auto& Canvas : GlobalCanvases)
	{
		Canvas->Render();
	}

	//If debug profiling is enabled, draw debug spheres/boxes
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


/// <summary>
/// Load a given world as the world context and mark previous for deletion
/// </summary>
/// <param name="World"></param>
void EngineCore::LoadWorld(std::shared_ptr<World> World)
{
	//Get current world
	if (CurrentWorld) {
		//Shut down the world
		CurrentWorld->Shutdown();
		//Mark for deletion: does not need explicit delete as it is a smart pointer
		EventManager::GetInstance()->AddEvent(std::make_shared<ScheduledLevelDeletion>(CurrentWorld));
	}

	//Setup new world
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
