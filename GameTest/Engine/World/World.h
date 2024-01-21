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
#include "../Managers/QuadTree.h"
#include "../Managers/SpriteManager.h"
class ObjectManager;
class Entity;
class EngineCore;
class CCamera;

#include <memory>

class World : public Object
{
public:
	//Class Name
	inline virtual const char* GetObjectClassName() override { return GetStaticClassName(); }
	inline static const char* GetStaticClassName() { return "World"; }

	//Constructor
	World(EngineCore* InEngine);
	virtual ~World();

	//Update
	virtual void OnBegin() override;
	virtual void Update(float DeltaTime);
	virtual void LateUpdate(float DeltaTime);
	virtual void FixedUpdate();
	virtual void Render();
	virtual void Shutdown() override;

public: // Game State Methods
	inline GameState* GetWorldGameState() { return WorldGameState.get(); };
public: // Event Handler Methods
	inline EventManager* GetWorldEventManager() { return WorldEventManager.get(); };
public: // Camera Methods
	inline void SetActiveCamera(CCamera* InCamera) { ActiveCamera = InCamera; };
	inline CCamera* GetActiveCamera() { return ActiveCamera; }
public: //Quad Tree Methods
	inline void RegisterCollisionEntity(CRigidBody* InBody) { WorldQuadTree->InsertNode(InBody->Position, InBody); }
	inline void UnRegisterCollisionEntity(CRigidBody* InBody) { WorldQuadTree->RemoveObject(InBody); }

public: // Object Managment Methods
	//Getter
	inline ObjectManager* GetWorldObjectManager() { return WorldObjectManager.get(); }
	//Creation Wrappers
	template <class Type>
	Type* CreateEntity();

	template <class Type>
	Type* CreateComponent(Entity* InEntity = nullptr);

public: // Sprite Manager
	inline void SetSpriteManager(SpriteManager* InSpriteManager) { EngineSpriteManager = InSpriteManager; }; //DEPRECATE
	inline SpriteManager* GetEngineSpriteManager() { return EngineSpriteManager; };							//DEPRECATE

protected: // Methods / Members
	
	//Engine References
	EngineCore* WorldEngine = nullptr; //DEPRECATE

	//Camera
	CCamera* ActiveCamera = nullptr;

	//Game State
	std::unique_ptr<GameState> WorldGameState;
	//Event Manager
	std::unique_ptr<EventManager> WorldEventManager;
	//Object Manager
	std::unique_ptr<ObjectManager> WorldObjectManager;
	//Quad Tree
	std::unique_ptr<QuadTree> WorldQuadTree;
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
