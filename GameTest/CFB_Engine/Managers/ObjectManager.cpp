#include "stdafx.h"
#include "ObjectManager.h"

#include "../Component/AllComponents.h"

//Delete all the objects
ObjectManager::~ObjectManager()
{
	//Clear all the vector
	for (auto &VectorPair : Entities)
	{
		//Get the vector value
		VectorPair.second.clear();
	}
}

//UPDATe
void ObjectManager::Update(float DeltaTime)
{
	//TODO
}

//DRAW
void ObjectManager::Draw()
{
	//Draw all sprite components!
	for (auto &UniqueSpriteComponent : Components["CSprite"])
	{
		//SpriteComponent.get()

	}
}

//Removes component from the list if it matches
void ObjectManager::DestroyComponent(Component* InComponent)
{
	//Get Object Name
	std::string ObjectName = InComponent->GetObjectClassName();

	//If there are any components of this type
	if (!Components[ObjectName].empty())
	{
		//Iterate
		for (int i = 0; i < Components[ObjectName].size(); i++)
		{
			if (Components[ObjectName][i].get() == InComponent)
			{
				//Delete
				Components[ObjectName].erase(Components[ObjectName].begin() + i);
				//Components[ObjectName].erase(std::remove(Components[ObjectName].begin(), Components[ObjectName].end(), InComponent), Components[ObjectName].end());
				//m_ComponentMap[name].erase(std::remove(m_ComponentMap[name].begin(), m_ComponentMap[name].end(), nullptr), m_ComponentMap[name].end());
				return;
			}
		}
		//Attempt an erasure
		//Components[ObjectName].erase(std::remove(Components[ObjectName].begin(), Components[ObjectName].end(), { InComponent }), Components[ObjectName].end());
	}
}