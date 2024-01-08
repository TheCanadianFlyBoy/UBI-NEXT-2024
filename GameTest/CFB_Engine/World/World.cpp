#include "stdafx.h"
#include "World.h"
#include "../Managers/ObjectManager.h"

World::World()
{
	WorldObjectManager = std::make_unique<ObjectManager>(this);
	WorldEventManager = std::make_unique<EventManager>(this);
	WorldGameState = std::make_unique<GameState>(this);
}

/// <summary>
/// Passes update calls to appropriate managers
/// </summary>
/// <param name="DeltaTime">Time since last frame</param>
void World::Update(float DeltaTime)
{
	WorldObjectManager->Update(DeltaTime);
	WorldEventManager->ProcessEvents(DeltaTime);
	WorldGameState->Update(DeltaTime);

}

/// <summary>
/// Passes draw call to appropriate managers
/// </summary>
void World::Draw()
{
	//Object Draw
	WorldObjectManager->Draw();
}
