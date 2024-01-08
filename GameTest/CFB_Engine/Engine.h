#pragma once
/*
*	CFB Engine 
*	Instance of the engine, responsible for creating and managing global managers
*
*/

#include <memory>
#include <vector>

#include "World/World.h"

class SpriteManager;


class Engine
{
public:
	
	//Default constructor
	Engine();

	//Returns Sprite Manager
	inline SpriteManager* GetSpriteManager() { return EngineSpriteManager.get(); }

	//Deletes a world
	void DeleteWorld(World* InWorld);

public: //Factory Constructors

	template <class Type>
	Type* CreateWorld();


protected: // Members

	//Sprite Manager
	std::unique_ptr<SpriteManager> EngineSpriteManager;

	//World Vector
	std::vector<std::unique_ptr<World>> Worlds;

};

/// <summary>
/// Constructs a new world of the given type
/// </summary>
/// <typeparam name="Type"></typeparam>
/// <returns></returns>
template<class Type>
inline Type* Engine::CreateWorld()
{
	//Check we have actually passed in an entity, otherwise this code will be broken
	assert((std::is_base_of < World, Type>()));

	//Create a unique pointer for mem mgmt
	Entities[Type::GetStaticClassName()].push_back(std::make_unique<Type>(this));

	//Return ptr to new object
	return static_cast<Type*>(Entities[Type::GetStaticClassName()].back().get());
}
