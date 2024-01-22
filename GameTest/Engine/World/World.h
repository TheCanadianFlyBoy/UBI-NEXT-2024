#pragma once
/*
*	Engine - World
*	The archetype for all worlds in the game, containing managers and objects.
*
*/

#include "../Object/Object.h"
#include "../State/GameState.h"
#include "../Managers/EventManager.h" //TODO figure this out why it's needed?
#include "../Managers/ObjectManager.h"
#include "../Managers/QuadTree.h"
#include "../Managers/SpriteManager.h"

//Forward declaration
class ObjectManager;
class Entity;
class EngineCore;
class CCamera;
//Needed for smart pointers
#include <memory>

  //////////////////////////////////////////////////////////////////////////////////////////////////////
 ///									Header		Start											///
//////////////////////////////////////////////////////////////////////////////////////////////////////
class World : public Object
{
public:
	//Class Name
	inline virtual const char* GetObjectClassName() override { return GetStaticClassName(); }
	inline static const char* GetStaticClassName() { return "World"; }

	//Constructor
	World();
	virtual ~World();

	//Critical Gameloop Functions
	virtual void OnBegin() override;
	virtual void Update(float DeltaTime);
	virtual void LateUpdate(float DeltaTime);
	virtual void FixedUpdate();
	virtual void Render();
	virtual void Shutdown() override;

  //////////////////////////////////////////////////////////////////////////////////////////////////////
 ///									Getters/Setters												///
//////////////////////////////////////////////////////////////////////////////////////////////////////
public: // Game State Methods
	inline GameState* GetWorldGameState() { return WorldGameState.get(); };

public: // Event Handler Methods
	inline EventManager* GetWorldEventManager() { return EventManager::GetInstance(); };

public: // Camera Methods
	inline void SetActiveCamera(CCamera* InCamera) { ActiveCamera = InCamera; };
	inline CCamera* GetActiveCamera() { return ActiveCamera; }

public: //Quad Tree Methods
	inline void RegisterCollisionEntity(CRigidBody* InBody) { WorldQuadTree->InsertNode(InBody->Position, InBody); }
	inline void UnRegisterCollisionEntity(CRigidBody* InBody) { WorldQuadTree->RemoveObject(InBody); }

public: // Object Manager
	inline ObjectManager* GetWorldObjectManager() { return WorldObjectManager.get(); }

  //////////////////////////////////////////////////////////////////////////////////////////////////////
 ///							   Entity/Component Factory											///
//////////////////////////////////////////////////////////////////////////////////////////////////////
	//Creation Wrappers
	template <class Type>
	Type* CreateEntity();

	template <class Type>
	Type* CreateComponent(Entity* InEntity = nullptr);

public: // Sprite Manager
	//inline void SetSpriteManager(SpriteManager* InSpriteManager) { EngineSpriteManager = InSpriteManager; }; //DEPRECATE
	//inline SpriteManager* GetEngineSpriteManager() { return EngineSpriteManager; };							//DEPRECATE

public: //Helpers
	Actor* GetNearestActor(Vector2 InPoint, std::vector<Actor*> IgnoredActors = std::vector<Actor*>());

  //////////////////////////////////////////////////////////////////////////////////////////////////////
 ///									Protected Members											///
//////////////////////////////////////////////////////////////////////////////////////////////////////
protected: 	
	//Engine References
	//EngineCore* WorldEngine = nullptr; //DEPRECATED

	//Camera
	CCamera* ActiveCamera = nullptr;
	//Game State
	std::unique_ptr<GameState> WorldGameState;
	//Object Manager
	std::unique_ptr<ObjectManager> WorldObjectManager;
	//Quad Tree
	std::unique_ptr<QuadTree> WorldQuadTree;
	//Sprite Manager
	SpriteManager* EngineSpriteManager = nullptr;





};


  //////////////////////////////////////////////////////////////////////////////////////////////////////
 ///									Factory Implementation										///
//////////////////////////////////////////////////////////////////////////////////////////////////////
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
