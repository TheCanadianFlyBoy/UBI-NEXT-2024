#include "stdafx.h"
#include "ObjectManager.h"

#include "../Engine.h"
#include "../Component/AllComponents.h"
#include "../UI/UICanvas.h"
#include "../UI/UIWidget.h"

#include "../../Game/Object/Projectile.h" //TODO move to engine

//Delete all the objects
ObjectManager::~ObjectManager()
{
	//Clear all the vector
	for (auto &VectorPair : Entities)
	{
		VectorPair.second.clear();
	}
}

//UPDATe
void ObjectManager::Update(float DeltaTime)
{
	//Update Health
	for (auto& Health : Components["CHealth"])
	{
		if (Health->Active) {
			Health->Update(DeltaTime);
		}
	}

	//Update cameras
	for (auto& CameraPointer : Components["CCamera"])
	{
		//Update
		if (CameraPointer->Active) CameraPointer->Update(DeltaTime);
	}

	//Update Rigid Bodies
	for (auto& RigidBody : Components["CRigidBody"])
	{
		if (RigidBody->Active) {
			RigidBody->Update(DeltaTime);
		}
	}

	for (auto& ThisProjectile : Entities["Projectile"])
	{

		//If inactive, skip
		if (ThisProjectile->Active == false)
		{
			continue;
		}

		Projectile* ProjectilePointer = static_cast<Projectile*>(ThisProjectile.get());

		if (ProjectilePointer->GetActorLocation().x > KillBoundsUpper.x ||
			ProjectilePointer->GetActorLocation().y > KillBoundsUpper.y ||
			ProjectilePointer->GetActorLocation().x < KillBoundsLower.x ||
			ProjectilePointer->GetActorLocation().y < KillBoundsLower.y
		)
		{
			ProjectilePointer->Shutdown();
		}
	}

}

/// <summary>
/// Handles late updates, such as resetting data structures
/// </summary>
/// <param name="DeltaTime"></param>
void ObjectManager::LateUpdate(float DeltaTime)
{
	//Handle moving on the registry
	for (auto& RigidBody : Components["CRigidBody"])
	{
		RigidBody->LateUpdate(DeltaTime);
	}
}

//DRAW
void ObjectManager::Render(CCamera* InCamera)
{
	//Draw all sprite components!
	for (auto &UniqueSpriteComponent : Components["CSprite"])
	{
		//We know this is a sprite, so we cast it!
		//UniqueSpriteComponent->Render(InCamera);

		if (UniqueSpriteComponent->Active)	static_cast<CSprite*>(UniqueSpriteComponent.get())->Render(InCamera);

	}

	//Draw all UI elements
	for (auto& Canvas : Canvases)
	{
		if (Canvas->Active) Canvas->Render();
	}

	//Debug draws
	if (ENGINE_DEBUG_MODE) 
	{
		for (auto& RigidBody : Components["CRigidBody"])
		{
			if (RigidBody->Active) RigidBody->Render(InCamera);
		}
	}

}

//Call shutdown on all relevant entities/components
void ObjectManager::Shutdown()
{
	//Clear all the vector
	for (auto& VectorPair : Entities)
	{
		for (auto& ThisEntity : VectorPair.second)
		{
			ThisEntity->Shutdown();
		}
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