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

namespace Debug
{

	inline void DrawLine(Vector2 Start, Vector2 End, Color3 Color = Color3(1.f)) { App::DrawLine(Start.x, Start.y, End.x, End.y, Color.r, Color.g, Color.b); }

	inline void DrawCircle(Vector2 Position, float Radius, int Segments = 12, Color3 Color = Color3(1.f)) {
		std::vector<Vector2> Points = MathOps::CreateCirclePoints(Radius, Segments);
		for (int i = 0; i < Points.size(); i++)
		{
			int j = i > 0 ? i - 1 : Points.size() - 1;
			DrawLine(Position + Points[i], Position + Points[j], Color);
		}
	}


} //namespace Debug
