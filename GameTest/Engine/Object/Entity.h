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
#include "../Math/Vector2.h"

class ObjectManager;
class World;

class Entity : public Object
{
public: //Setup/Common

	//Class Name
	inline virtual const char* GetObjectClassName() override { return GetStaticClassName(); }
	inline static const char* GetStaticClassName() { return "Entity"; }

	//Constructor with optional params
	Entity(World* InWorld = nullptr) : ThisWorld(InWorld) {};
	//Shutdown
	virtual void Shutdown() override;
	
	//Destructor
	virtual ~Entity();

public: //Common Gameplay Methods
	
public: //Getters

	//World
	inline World* GetWorld() { return ThisWorld; };

	//Components
	template <class Type>
	Type* GetComponentOfClass();


public: //Adders

	//Utilizes world factory to create a component of given type
	template <class Type> 
	Type* CreateComponent();

protected: //Members

	//World Reference
	World* ThisWorld = nullptr; //TODO refactor to be the world

	//Components - vector to allow for adding, removal at runtime
	std::vector<Component*> Components;

protected: //Helper Functions

	//Gets the index of a given component
	int GetIndexOfComponent(Component* InComponent);

	//Gets the first index of a type of component
	template <class Type>
	int GetIndexOfComponentClass();

};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 

/// <summary>
/// Creates a component of the given type, and returns a pointer to it (or null if unable to create)
/// </summary>
/// <typeparam name="Type">Class of Component to Create</typeparam>
/// <returns>Pointer to the Component, null if unable to create</returns>
template<class Type>
inline Type* Entity::CreateComponent()
{
	//THIS MUST BE A COMPONENT
	assert((std::is_base_of < Component, Type>()));

	//Create a new component with this as owner
	Type* NewComponent = ThisWorld->CreateComponent<Type>(this);
	//Save it for reference
	Components.push_back(NewComponent);

	return NewComponent;

}

/// <summary>
/// Gets the first component of the given class type, and returns a pointer to it
/// </summary>
/// <typeparam name="Type">Component Class</typeparam>
/// <returns>Pointer to component, null if not present</returns>
template<class Type>
Type* Entity::GetComponentOfClass()
{
	//Ensure that we have a component class passed in
	assert((std::is_base_of < Component, Type>()));

	//Check for an index
	int index = GetIndexOfComponentClass<Type>();

	//We have one!
	if (index >= 0)
	{
		return static_cast<Type*>(Components[index]);
	}

	//Nothing found, return null
	return nullptr;
}

/// <summary>
/// Gets the first index of a given component class
/// </summary>
/// <typeparam name="Type">Component Class</typeparam>
/// <returns>Index of component, or -1 if not present</returns>
template<class Type>
int Entity::GetIndexOfComponentClass()
{
	//Ensure that we have a component class passed in
	assert((std::is_base_of < Component, Type>()));

	//Now we search or our components
	for (int i = 0; i < Components.size(); i++)
	{
		//Current Component Variable
		Component* CurrentComponent = Components[i];

		//Check if it is the correct type
		if (CurrentComponent->GetObjectClassName() == Type::GetStaticClassName())
		{
			//Return index
			return i;
		}

	}

	//Failure, return -1
	return -1;
}

