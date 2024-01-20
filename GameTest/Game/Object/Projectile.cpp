#include "stdafx.h"
#include "Projectile.h"

/// <summary>
/// Creates the rigid body necessary for the projectile
/// </summary>
/// <param name="InWorld"></param>
Projectile::Projectile(World* InWorld) : Actor(InWorld)
{
	ProjectileBody = CreateComponent<CRigidBody>();
	ProjectileBody->MakeCollisionCircle(Vector2(0.f), 15.f);
}
