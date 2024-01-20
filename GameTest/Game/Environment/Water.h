#pragma once
/*
*	ANGRY SHIPS - Water
*	A basic water system for the ships
*
*/

#include "../../Engine/Object/Actor.h"
#include "../../Engine/Component/CameraComponent.h"

class WaterRenderer : public Actor
{
public:

	WaterRenderer(World* InWorld = nullptr);


	virtual void Update(float DeltaTime) override;
	virtual void Render(CCamera* InCamera = nullptr);


protected:
	std::vector<Vector2> WaterPoints;
	
	int PointNumber = 1000;

	float PointDistance = 18.f;

	float CurrentWaterValue = 0.f;

	float WaterLevel = 225.f;

};

