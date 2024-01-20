#pragma once
/*
*	CFB Engine - Debug
*	A suite of easy to use tools for debugging
*
*/

#include "../../App/app.h"
#include "../Math/MathOps.h"
#include "../Math/Vector2.h"
#include "../Math/Vector3.h"



#include "../Component/CameraComponent.h"


namespace Debug
{

	inline void DrawLine(Vector2 Start, Vector2 End, Color3 Color = Color3(1.f)) { App::DrawLine(Start.x, Start.y, End.x, End.y, Color.r, Color.g, Color.b); }
	inline void DrawLineInWorld(Vector2 Start, Vector2 End, ::CCamera* InCamera, Color3 Color = Color3(1.f))
	{
		DrawLine(Start - InCamera->GetCameraOrigin(), End - InCamera->GetCameraOrigin(), Color);
	}

	inline void DrawCircle(Vector2 Position, float Radius, int Segments = 12, Color3 Color = Color3(1.f)) {
		std::vector<Vector2> Points = MathOps::CreateCirclePoints(Radius, Segments);
		for (int i = 0; i < Points.size(); i++)
		{
			int j = i > 0 ? i - 1 : Points.size() - 1;
			DrawLine(Position + Points[i], Position + Points[j], Color);
		}
	}
	inline void DrawCircleInWorld(Vector2 Position, float Radius, ::CCamera* InCamera, int Segments = 12, Color3 Color = Color3(1.f)) {
		DrawCircle(Position - InCamera->GetCameraOrigin(), Radius, Segments, Color);
	}

	inline void DrawRectangle(Vector2 Position, Vector2 Bounds, Color3 Color = Color3(1.f), bool Centred = true)
	{
		if (Centred) Position -= Bounds / 2;

		Vector2 TopLeft = Position;
		Vector2 TopRight = Position + Vector2(Bounds.x, 0.f);
		Vector2 BottomLeft = Position + Vector2(0.f, Bounds.y);
		Vector2 BottomRight = Position + Bounds;

		DrawLine(TopLeft, TopRight, Color);
		DrawLine(TopRight, BottomRight, Color);
		DrawLine(BottomRight, BottomLeft, Color);
		DrawLine(BottomLeft, TopLeft, Color);


	}
	inline void DrawRectangleInWorld(Vector2 Position, Vector2 Bounds, ::CCamera* InCamera, Color3 Color = Color3(1.f), bool Centred = true)
	{
		DrawRectangle(Position - InCamera->GetCameraOrigin(), Bounds, Color, Centred);
	}


} //namespace Debug
