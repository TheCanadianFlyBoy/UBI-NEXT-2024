#pragma once
/*
*	CFB Engine - Entity
*	The archetype for all Entities within the ECS.
*
*/

#include <vector>
#include <memory>
#include <type_traits>
#include <assert.h>

#include "Object.h"
#include "../Component/Component.h"


class Entity : public Object
{
public: //Setup/Common
	//Constructor
	Entity() {};

	~Entity();

	//Components - vector to allow for adding, removal at runtime
	std::vector<std::unique_ptr<Component>> Components;

	//Class Name
	inline virtual const char* GetObjectClassName() override { return GetStaticClassName(); }
	inline static const char* GetStaticClassName() { return "Entity"; }


public: //Adders

	/// <summary>
	/// Creates a component of the given type, and returns a pointer to it (or null if unable to create)
	/// </summary>
	/// <typeparam name="Type">Class of Component to Create</typeparam>
	/// <returns>Pointer to the Component, null if unable to create</returns>
	template <class Type> 
	Type* CreateComponent();

};


//TEMPLATE DEFINITIONS
template<class Type>
inline Type* Entity::CreateComponent()
{
	//THIS MUST BE A COMPONENT
	assert((std::is_base_of < Component, Type>()));

	//Add to vector
	Components.push_back(std::unique_ptr<Type>(new Type(this))); //Instantiate with a reference to self

	//Return ptr to ptr
	return static_cast<Type*>(Components.back().get());
}
