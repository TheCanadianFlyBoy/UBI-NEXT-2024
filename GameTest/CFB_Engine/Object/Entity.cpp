#include "stdafx.h"

#include "Entity.h"
#include "../Component/Component.h"

//Delete all components
Entity::~Entity()
{
	//Components.clear();
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