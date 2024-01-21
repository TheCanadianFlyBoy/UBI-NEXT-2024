#pragma once
/*
*	CFB Engine - Object Manager
*	Provides a reusable and robust way to manage object memory in the gamespace.
* 
*/

#include <map>		//Map for all vectors
#include <vector>	//Storage for objects
#include <memory>	//Pointers for mem mgmt
#include <string>	//Key for map

#include "../Object/Entity.h"
#include "../UI/UICanvas.h"

class CSimpleSprite;
class CCamera;
class World;
class UICanvas;
class UIWidget;


class ObjectManager : public Entity {

public: 
	//Class Name
	inline virtual const char* GetObjectClassName() override { return GetStaticClassName(); }
	inline static const char* GetStaticClassName() { return "ObjectManager"; }

	//Constructor
	ObjectManager(World* InWorld = nullptr) : Entity(InWorld) {};
	
	//Destructor
	~ObjectManager();

public: //Methods

	virtual void OnBegin() override;
	virtual void Update(float DeltaTime);
	virtual void LateUpdate(float DeltaTime);
	virtual void FixedUpdate();
	virtual void Render(CCamera* InCamera = nullptr);
	virtual void Shutdown() override;


public: //Add/Removal
	void DestroyComponent(Component* InComponent);



public: //Getters

	inline int GetEntityInstanceCount(std::string ClassName) { return int(Entities[ClassName].size()); }

	Actor* GetNearestActor(Vector2 InPosition, std::vector<Actor*> IgnoredActors);

public: //Factory Constructors

	template <class Type>
	Type* CreateEntity();

	template <class Type>
	Type* CreateComponent(Entity* InEntity = nullptr);

	template <class Type>
	Type* CreateWidget(UICanvas* InCanvas = nullptr);

	template <class Type>
	Type* CreateCanvas();

protected: // Helpers
	template <class Type>
	Type* GetEntityOfClass();


protected: //Members

	//Entity List - Unique because we have ownership!
	std::map<std::string, std::vector<std::unique_ptr<Entity>>> Entities;
	//Component List - Shared ownership with entities
	std::map<std::string, std::vector<std::unique_ptr<Component>>> Components; //TODO CONVERT TO RAW POINTERS
	//World List
	//UI List
	std::vector<std::unique_ptr<UICanvas>> Canvases; //TODO z order

	Vector2 KillBoundsLower = Vector2(-200.f, -100.f);
	Vector2 KillBoundsUpper = Vector2(20000.f, 1200.f);



};


/// <summary>
/// Creates an entity within the Object Manager, and returns a non-managed pointer (raw)
/// </summary>
/// <typeparam name="Type">Type of Entity</typeparam>
/// <returns>Pointer to Entity</returns>
template<class Type>
inline Type* ObjectManager::CreateEntity()
{
	//Check we have actually passed in an entity, otherwise this code will be broken
	assert((std::is_base_of < Entity, Type>()));

	//Object pooled? Use it
	if (Type* ExistingEntity = GetEntityOfClass<Type>()) {
		ExistingEntity->OnBegin();
		return ExistingEntity;
	}

	//Create a unique pointer for mem mgmt
	Entities[Type::GetStaticClassName()].push_back(std::make_unique<Type>(ThisWorld));

	//Get unmanaged pointer to new object
	Type* NewObject = static_cast<Type*>(Entities[Type::GetStaticClassName()].back().get());

	//Setup default name
	std::string DefaultName = NewObject->GetStaticClassName() + std::to_string(Entities[Type::GetStaticClassName()].size());

	//Stamp default name
	Entities[Type::GetStaticClassName()].back().get()->InstanceName = DefaultName;

	//Return ptr to new object
	return static_cast<Type*>(Entities[Type::GetStaticClassName()].back().get());
};


/// <summary>
/// Creates a component within the object manager and returned a non-managed pointer (raw)
/// </summary>
/// <typeparam name="Type"></typeparam>
/// <param name="InEntity"></param>
/// <returns></returns>
template<class Type>
inline Type* ObjectManager::CreateComponent(Entity* InEntity)
{
	//Check we have actually passed in an entity, otherwise this code will be broken
	assert((std::is_base_of <Component, Type>()));

	//Create a unique pointer for mem mgmt
	Components[Type::GetStaticClassName()].push_back(std::make_unique<Type>(InEntity));

	//Return ptr to new object (we've already asserted so static cast is safe)
	return static_cast<Type*>( Components[Type::GetStaticClassName()].back().get());
}

/// <summary>
/// Creates a widget
/// </summary>
/// <typeparam name="Type"></typeparam>							 //TODO fix these descs
/// <param name="InCanvas"></param>
/// <returns></returns>
template<class Type>
inline Type* ObjectManager::CreateWidget(UICanvas* InCanvas)
{
	//Check we have actually passed in an entity, otherwise this code will be broken
	assert((std::is_base_of <UIWidget, Type>()));

	//Create a unique pointer for mem mgmt
	return InCanvas->AddWidget<Type>();

}


/// <summary>
/// Creates a canvas 
/// </summary>
/// <typeparam name="Type"></typeparam>
/// <returns></returns>
template<class Type>
inline Type* ObjectManager::CreateCanvas()
{
	//Check we have actually passed in an entity, otherwise this code will be broken
	assert((std::is_base_of <UICanvas, Type>()));

	//Create a unique pointer for mem mgmt
	Canvases.push_back(std::make_unique<Type>());

	//Return ptr to new object (we've already asserted so static cast is safe)
	return static_cast<Type*>(Canvases.back().get());
}

/// <summary>
/// Gets an entity of the given class
/// </summary>																	//TODO fix desc
/// <typeparam name="Type"></typeparam>
/// <returns></returns>
template<class Type>
inline Type* ObjectManager::GetEntityOfClass()
{
	//Check we have actually passed in an entity, otherwise this code will be broken
	assert((std::is_base_of < Entity, Type>()));

	//Iterate
	for (auto& ThisEntity : Entities[Type::GetStaticClassName()])
	{
		if (!ThisEntity->Active)
		{
			ThisEntity->OnBegin();
			return static_cast<Type*>(ThisEntity.get());
		}
	}

	return nullptr;
}
;
