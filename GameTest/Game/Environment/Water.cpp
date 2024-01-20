#include "stdafx.h"

#include"../../Engine/Common.h"
#include "Water.h"

WaterRenderer::WaterRenderer(World* InWorld) : Actor(InWorld)
{
	
}

void WaterRenderer::OnBegin()
{
	Actor::OnBegin();

	if (WaterPoints.empty())
	{
		//Generate points
		for (int i = 0; i < PointNumber; i++)
		{
			WaterPoints.push_back(GetActorLocation() + Vector2(PointDistance * i, WaterLevel));
		}
	}
}

void WaterRenderer::Update(float DeltaTime)
{
	//Update the wave value
	CurrentWaterValue += DeltaTime * 0.01f;

	for (int i = 0; i < WaterPoints.size() - 1; i++)
	{
		WaterPoints[i].y += sinf(CurrentWaterValue + WaterPoints[i].x + i/2.f) * 0.2f;
		WaterPoints[i].y += cosf(CurrentWaterValue + WaterPoints[i].x) * 0.2f;

	}

}

void WaterRenderer::Render(CCamera* InCamera)
{
	//Debug for now

	for (int i = 0; i < WaterPoints.size() - 1; i++)
	{
		Debug::DrawLine(WaterPoints[i] - InCamera->GetCameraOrigin(), WaterPoints[i + 1] - InCamera->GetCameraOrigin(), Color3(0.f, 0.15f, 1.f));
	}


}