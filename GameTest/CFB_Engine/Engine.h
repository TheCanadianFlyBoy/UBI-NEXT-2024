#pragma once
/*
*	CFB Engine 
*	Instance of the engine, responsible for creating and managing global managers
*
*/

#include <memory>
#include <vector>

#include "World/World.h"

#define ENGINE_DEBUG_MODE true

//class SpriteManager;
class UIManager;

#define ENGINE EngineCore::GetInstance()

class EngineCore
{
	DECLARE_SINGLE(EngineCore); // Declare this as a singleton system (only one instance ever)

public: // Methods
	
	//Initializes member elements
	void Initialize();

	void Update(float DeltaTime);
	void LateUpdate(float DeltaTime);
	void Render();

	//Returns current world
	inline World* GetCurrentWorld() { return CurrentWorld; }
	void LoadWorld(World* InWorld);

	//Returns Sprite Manager
	inline SpriteManager* GetSpriteManager() { return SpriteManager::GetInstance(); }

	//Deletes a world
	void DeleteWorld(World* InWorld);

public: //Factory Constructors

	template <class Type>
	Type* CreateWorld();

	template <class Type>
	Type* CreateGlobalWidget(UICanvas* InCanvas = nullptr);

	template <class Type>
	Type* CreateGlobalCanvas();

protected: // Members

	World* CurrentWorld = nullptr;

	//World Vector
	std::vector<std::unique_ptr<World>> Worlds; // TODO MAP for saving names
	//Persistent Canvases
	std::vector <std::unique_ptr<UICanvas>> GlobalCanvases;

public: //Helpers
	Vector2 GetMousePosition();

};

/// <summary>
/// Constructs a new world of the given type
/// </summary>
/// <typeparam name="Type"></typeparam>
/// <returns></returns>
template<class Type>
inline Type* EngineCore::CreateWorld()
{
	//Check we have actually passed in an entity, otherwise this code will be broken
	assert((std::is_base_of < World, Type>()));

	//Create a unique pointer for mem mgmt
	Worlds.push_back(std::make_unique<Type>(this));

	//Return ptr to new object
	return static_cast<Type*>(Worlds.back().get());
}

/// <summary>
/// Creates a widget
/// </summary>
/// <typeparam name="Type"></typeparam>							 //TODO fix these descs
/// <param name="InCanvas"></param>
/// <returns></returns>
template<class Type>
inline Type* EngineCore::CreateGlobalWidget(UICanvas* InCanvas)
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
inline Type* EngineCore::CreateGlobalCanvas()
{
	//Check we have actually passed in an entity, otherwise this code will be broken
	assert((std::is_base_of <UICanvas, Type>()));

	//Create a unique pointer for mem mgmt
	GlobalCanvases.push_back(std::make_unique<Type>());

	//Return ptr to new object (we've already asserted so static cast is safe)
	return static_cast<Type*>(GlobalCanvases.back().get());
}