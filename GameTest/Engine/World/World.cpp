#include "stdafx.h"
#include "World.h"
#include "../Managers/ObjectManager.h"
#include "../Managers/Quadtree.h"
#include "../Engine.h"

World::World(EngineCore* InEngine) : WorldEngine(InEngine)
{
	WorldObjectManager = std::make_unique<ObjectManager>(this);
	WorldEventManager = std::make_unique<EventManager>(this);
	WorldGameState = std::make_unique<GameState>(this);
	EngineSpriteManager = InEngine->GetSpriteManager();

	WorldQuadTree = std::make_unique<QuadTree>();

	bool g = true;
}

World::~World()
{
}

/// <summary>
/// Call initial begin on everything
/// </summary>
void World::OnBegin()
{
	WorldObjectManager->OnBegin();
	WorldEventManager->OnBegin();
	WorldGameState->OnBegin();
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
	WorldQuadTree->Query();
}

/// <summary>
/// Handles late update for all objects
/// </summary>
/// <param name="DeltaTime"></param>
void World::LateUpdate(float DeltaTime)
{
	WorldObjectManager->LateUpdate(DeltaTime);
}

/// <summary>
/// Passes draw call to appropriate managers
/// </summary>
void World::Render()
{
	//Object Draw
	WorldObjectManager->Render(ActiveCamera);
}

void World::Shutdown()
{
	//Flush events
	WorldEventManager->Shutdown();

	//Game State
	WorldGameState->Shutdown();

	//Clear object manager
	WorldObjectManager->Shutdown();
	WorldObjectManager.reset();

	//Quad Tree
	WorldQuadTree->ClearTree();

}
