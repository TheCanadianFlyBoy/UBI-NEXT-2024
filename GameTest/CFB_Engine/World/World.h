#pragma once
/*
*	CFB Engine - World
*	The archetype for all worlds in the game, containing managers and objects.
*
*/

#include "../Object/Object.h"
#include "../State/GameState.h"
#include "../Managers/EventManager.h" //TODO figure this out why it's needed?
#include "../Managers/ObjectManager.h"
class ObjectManager;
class Entity;
class SpriteManager;
class Engine;
class CCamera;

#include <memory>

class World : public Object
{
public:
	//Class Name
	inline virtual const char* GetObjectClassName() override { return GetStaticClassName(); }
	inline static const char* GetStaticClassName() { return "World"; }

	//Constructor
	World(Engine* InEngine);

	//Update
	virtual void Update(float DeltaTime);
	virtual void Draw();

public: // Game State Methods
	inline GameState* GetWorldGameState() { return WorldGameState.get(); };
public: // Event Handler Methods
	inline EventManager* GetWorldEventManager() { return WorldEventManager.get(); };
public: // Camera Methods
	inline void SetActiveCamera(CCamera* InCamera) { ActiveCamera = InCamera; };
	inline CCamera* GetActiveCamera() { return ActiveCamera; }

public: // Object Managment Methods
	//Getter
	inline ObjectManager* GetWorldObjectManager() { return WorldObjectManager.get(); }
	//Creation Wrappers
	template <class Type>
	Type* CreateEntity();

	template <class Type>
	Type* CreateComponent(Entity* InEntity = nullptr);

public: // Sprite Manager
	inline void SetSpriteManager(SpriteManager* InSpriteManager) { EngineSpriteManager = InSpriteManager; };
	inline SpriteManager* GetEngineSpriteManager() { return EngineSpriteManager; };

protected: // Methods / Members
	
	//Engine References
	Engine* WorldEngine = nullptr;

	//Camera
	CCamera* ActiveCamera = nullptr;

	//Game State
	std::unique_ptr<GameState> WorldGameState;
	//Event Manager
	std::unique_ptr<EventManager> WorldEventManager;
	//Object Manager
	std::unique_ptr<ObjectManager> WorldObjectManager;
	//Sprite Manager
	SpriteManager* EngineSpriteManager = nullptr;





};

// TEMPLATES
template<class Type>
inline Type* World::CreateEntity()
{
	return WorldObjectManager->CreateEntity<Type>();
}

template<class Type>
inline Type* World::CreateComponent(Entity* InEntity)
{
	return WorldObjectManager->CreateComponent<Type>(InEntity);
}
