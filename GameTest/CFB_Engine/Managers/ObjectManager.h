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

class Object;
class Entity;
class CSimpleSprite;


class ObjectManager {

public: 

	//Constructor
	ObjectManager() {};
	
	//Destructor
	~ObjectManager();

public: //Methods

	virtual void Update(float DeltaTime);
	virtual void Draw();

public: //Add/Removal
	void DestroyComponent(Component* InComponent);

public: //Factory Constructors

	template <class Type>
	Type* CreateEntity();

	template <class Type>
	Type* CreateComponent(Entity* InEntity = nullptr);


protected: //Members

	//Entity List - Unique because we have ownership!
	std::map<std::string, std::vector<std::unique_ptr<Entity>>> Entities;
	//Component List - Shared ownership with entities
	std::map<std::string, std::vector<std::unique_ptr<Component>>> Components; //TODO CONVERT TO RAW POINTERS
	//World List
	//TODO



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

	//Create a unique pointer for mem mgmt
	Entities[Type::GetStaticClassName()].push_back(std::make_unique<Type>(this));

	//Return ptr to new object
	return static_cast<Type*>(Entities[Type::GetStaticClassName()].back().get());
};


template<class Type>
inline Type* ObjectManager::CreateComponent(Entity* InEntity)
{
	//Check we have actually passed in an entity, otherwise this code will be broken
	assert((std::is_base_of <Component, Type>()));

	//Create a unique pointer for mem mgmt
	Components[Type::GetStaticClassName()].push_back(std::make_unique<Type>(InEntity));

	//Return ptr to new object (we've already asserted so static cast is safe)
	return static_cast<Type*>( Components[Type::GetStaticClassName()].back().get());
};
