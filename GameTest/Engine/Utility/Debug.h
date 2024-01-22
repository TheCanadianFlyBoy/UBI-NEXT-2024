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

class EngineProfiler;

/// <summary>
/// Namespace containing helpers for drawing debug information
/// </summary>
namespace Debug
{
	/// <summary>
	/// Draws a line in 
	/// </summary>
	/// <param name="Start"></param>
	/// <param name="End"></param>
	/// <param name="Color"></param>
	inline void DrawLine(Vector2 Start, Vector2 End, Color3 Color = Color3(1.f)) { App::DrawLine(Start.x, Start.y, End.x, End.y, Color.r, Color.g, Color.b); }
	/// <summary>
	/// Draws a line in world space
	/// </summary>
	/// <param name="Start"></param>
	/// <param name="End"></param>
	/// <param name="InCamera"></param>
	/// <param name="Color"></param>
	inline void DrawLineInWorld(Vector2 Start, Vector2 End, ::CCamera* InCamera, Color3 Color = Color3(1.f))
	{
		DrawLine(Start - InCamera->GetCameraOrigin(), End - InCamera->GetCameraOrigin(), Color);
	}

	/// <summary>
	/// Draws a circle in screen space
	/// </summary>
	/// <param name="Position"></param>
	/// <param name="Radius"></param>
	/// <param name="Segments"></param>
	/// <param name="Color"></param>
	inline void DrawCircle(Vector2 Position, float Radius, int Segments = 12, Color3 Color = Color3(1.f)) {
		std::vector<Vector2> Points = MathOps::CreateCirclePoints(Radius, Segments);
		for (int i = 0; i < Points.size(); i++)
		{
			int j = i > 0 ? i - 1 : int(Points.size()) - 1;
			DrawLine(Position + Points[i], Position + Points[j], Color);
		}
	}

	/// <summary>
	/// Draws a circle in world space
	/// </summary>
	/// <param name="Position"></param>
	/// <param name="Radius"></param>
	/// <param name="InCamera"></param>
	/// <param name="Segments"></param>
	/// <param name="Color"></param>
	inline void DrawCircleInWorld(Vector2 Position, float Radius, ::CCamera* InCamera, int Segments = 12, Color3 Color = Color3(1.f)) {
		DrawCircle(Position - InCamera->GetCameraOrigin(), Radius, Segments, Color);
	}

	/// <summary>
	/// Draws a rectangle in screen space
	/// </summary>
	/// <param name="Position"></param>
	/// <param name="Bounds"></param>
	/// <param name="Color"></param>
	/// <param name="Centred"></param>
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

	/// <summary>
	/// Draws a rectangle in world space based on inputs
	/// </summary>
	/// <param name="Position"></param>
	/// <param name="Bounds"></param>
	/// <param name="InCamera"></param>
	/// <param name="Color"></param>
	/// <param name="Centred"></param>
	inline void DrawRectangleInWorld(Vector2 Position, Vector2 Bounds, ::CCamera* InCamera, Color3 Color = Color3(1.f), bool Centred = true)
	{
		DrawRectangle(Position - InCamera->GetCameraOrigin(), Bounds, Color, Centred);
	}

	//MACRO redef, low pri change for best practices TODO

	/// <summary>
	/// Draws text in screen space
	/// </summary>
	/// <param name="InPosition"></param>
	/// <param name="Text"></param>
	/// <param name="Color"></param>
	/// <param name="Font"></param>
	inline void DrawText(Vector2 InPosition, std::string Text, Color3 Color = Color3(1.f), void* Font = (void*)8U)
	{
		App::Print(InPosition.x, InPosition.y, Text.c_str(), Color.r, Color.g, Color.b, Font);
	}

	/// <summary>
	/// Prints to engine profiler
	/// </summary>
	/// <param name="InText"></param>
	void PrintLine(std::string InText);




} //namespace Debug

