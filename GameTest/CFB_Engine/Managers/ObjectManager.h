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


class ObjectManager {

public: 

	//Constructor
	ObjectManager() {};
	
	//Destructor
	~ObjectManager();

public: //Factory Constructors

	template <class Type>
	Type* CreateEntity();


protected: //Members

	std::map<std::string, std::vector<std::unique_ptr<Entity>>> Entities;



};



template<class Type>
inline Type* ObjectManager::CreateEntity()
{
	//Check we have actually passed in an entity, otherwise this code will be broken
	assert((std::is_base_of < Entity, Type>()));

	//Create a unique pointer for mem mgmt
	Entities[Type::GetStaticClassName()].push_back(std::make_unique<Entity>());
	
	//Return ptr to new object
	return Entities[Type::GetStaticClassName()].back().get();
}
