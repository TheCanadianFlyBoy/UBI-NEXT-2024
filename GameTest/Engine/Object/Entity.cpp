#include "stdafx.h"

#include "Entity.h"
#include "../Component/Component.h"
#include "../Component/TransformComponent.h"
#include "../World/World.h"

/// <summary>
/// Reactivation or first activation
/// </summary>
void Entity::OnBegin()
{
	Object::OnBegin();

	for (auto& ThisComponent : Components)
	{
		ThisComponent->OnBegin();
	}
}

/// <summary>
/// On level end or deletion
/// </summary>
void Entity::Shutdown()
{
	//Set inactive
	Object::Shutdown();

	//Shutdown components
	for (Component* ThisComponent : Components)
	{
		ThisComponent->Shutdown();
	}

	//Strip of components
	//Components.clear();

}

//Delete all components
Entity::~Entity()
{
	Components.clear();
}
Vector2 Entity::GetEntityLocation()
{
	if (CTransform* Transform = GetComponentOfClass<CTransform>())
		return Transform->GetPosition();

	return Vector2();
}
/// <summary>
/// Takes a pointer to a component and attempts to find it's index in the component vector;
/// </summary>
/// <param name="InComponent">Existing Component</param>
/// <returns>Index or -1</returns>
int Entity::GetIndexOfComponent(Component* InComponent)
{
	//Iterate
	for (int i = 0; i < Components.size(); i++)
	{
		//Check if we are the same
		if (Components[i] == InComponent)
		{
			//Found it!
			return i;
		}
	}

	//No result found, return -1
	return -1;
}
