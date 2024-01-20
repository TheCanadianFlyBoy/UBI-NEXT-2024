#include "stdafx.h"
#include "Collision.h"
#include "../Utility/Debug.h"

#include "../Engine.h"

#include <cassert>

bool CollisionBox::CircleToAABB(CollisionCircle& Circle, CollisionLine& CircleTrajectory, CollisionInfo& OutInfo)
{
	//Get vector between centers
	Vector2 CenterDifference = PositionCentred ? Position - Circle.Position : Position - Circle.Position + (Bounds / 2);
	//Get clamped 
	Vector2 ClampedDifference = Vector2(
		MathOps::FClamp(CenterDifference.x, -Bounds.x / 2, Bounds.x / 2),
		MathOps::FClamp(CenterDifference.y, -Bounds.y / 2, Bounds.y / 2)
	);

	//Calculate closest point to circle
	Vector2 ClosestPointToCircle = GetCentre() - ClampedDifference;

	//Distance to closest point
	Vector2 ToSurface = ClosestPointToCircle - Circle.Position;
	float DistanceSqr = ToSurface.LengthSquared();

	bool Result = (DistanceSqr <= Circle.Radius * Circle.Radius || PointToAABB(GetCentre() + CenterDifference));


	//Only when we hit something
	if (Result)
	{
		//Get edge
		Vector2 EdgeStart = GetMax();
		Vector2 EdgeEnd = GetMax();
		
		bool Top    = CollisionLine(GetMin(), Vector2(GetMax().x, GetMin().y)).PointToLine(ClosestPointToCircle);
		bool Left   = CollisionLine(GetMin(), Vector2(GetMin().x, GetMax().y)).PointToLine(ClosestPointToCircle);
		bool Right  = CollisionLine(GetMax(), Vector2(GetMax().x, GetMin().y)).PointToLine(ClosestPointToCircle);
		bool Bottom = CollisionLine(GetMax(), Vector2(GetMin().x, GetMax().y)).PointToLine(ClosestPointToCircle);

		Vector2 Normal;

		if (Top)
		{
			Normal = Vector2::GetNormal(GetMin(), Vector2(GetMax().x, GetMin().y));
		}
		else if (Left)
		{
			Normal = Vector2::GetNormal(GetMin(), Vector2(GetMin().x, GetMax().y));
		}
		else if (Right)
		{
			Normal = Vector2::GetNormal(GetMax(), Vector2(GetMax().x, GetMin().y));
		}
		else {
			Normal = Vector2::GetNormal(GetMax(), Vector2(GetMin().x, GetMax().y));
		}

		//Setup outputs
		OutInfo.ImpactPoint = ClosestPointToCircle;
		OutInfo.PenetrationVector = ToSurface;
		OutInfo.PenetrationDepth = ToSurface.Length();
		OutInfo.Normal = Normal;

		ENGINE->GetCurrentWorld()->GetWorldEventManager()->AddEvent(new CollisionEvent(OutInfo));

		Debug::DrawLineInWorld(Position, (Position + Normal.GetNormalized()) * 40.f, ENGINE->GetCurrentWorld()->GetActiveCamera(), Color3(0.f, 1.f, 0.f));
	}

	//Check if in circle radius
	return Result;
}

bool CollisionBox::LineToAABB(CollisionLine& Line)
{
	CollisionLine Top = { Vector2(GetMin().x, GetMin().y), Vector2(GetMax().x, GetMin().y) };
	CollisionLine Left = { Vector2(GetMin().x, GetMin().y), Vector2(GetMin().x, GetMax().y) };
	CollisionLine Right = { Vector2(GetMax().x, GetMin().y), Vector2(GetMax().x, GetMax().y) };
	CollisionLine Bottom = { Vector2(GetMin().x, GetMax().y), Vector2(GetMax().x, GetMax().y) };

	return (Top.LineToLine(Line) || Left.LineToLine(Line) || Right.LineToLine(Line) || Bottom.LineToLine(Line));
}

bool CollisionCircle::LineToCircle(CollisionLine& Line)
{
	//Case 1: start/end points in circle
	if (Line.Start.DistanceFrom(Position) <= Radius || Line.End.DistanceFrom(Position) <= Radius) return true;
	float DotProduct = (Position.x - Line.Start.x) * (Line.End.x - Line.Start.x) + (Position.y - Line.Start.y) * (Line.End.y - Line.Start.y) / powf(Line.GetLength(), 2.f);
	//Closest point on line
	Vector2 ClosestPoint = Vector2(Line.Start.x + (DotProduct * Line.GetXSlope()), Line.Start.y + (DotProduct * Line.GetYSlope()));
	//Case 2: Not on line
	if (!Line.PointToLine(ClosestPoint)) return false;
	//Get distance
	float Distance = ClosestPoint.DistanceFrom(Position);
	//Case 3: Collision
	return (Distance <= Radius);
}

void CollisionUnitTest()
{
	bool test = false;

	//TEST FOR COLLISION
	CollisionBox Box1{ Vector2(10.f), Vector2(10.f) };
	CollisionBox Box2{ Vector2(5.f), Vector2(10.f) };
	CollisionBox Box3{ Vector2(50.f), Vector2(10.f) };
	CollisionLine Line1{ Vector2(10.f, 2.f), Vector2(20.f, 28.f) };
	CollisionLine Line2{ Vector2(8.f), Vector2(18.f) };
	CollisionLine Line3{ Vector2(80.f), Vector2(40.f) };
	CollisionCircle Circle1{ Vector2(10.f), 5.f };
	CollisionCircle Circle2{ Vector2(8.f), 5.f };
	CollisionCircle Circle3{ Vector2(80.f), 5.f };
	//Circle
	//assert(Circle1.CircleToCircle(Circle2));
	//assert(Circle1.LineToCircle(Line1));
	//assert(Circle1.PointToCircle(Vector2(10.f)));
	//assert(!Circle1.CircleToCircle(Circle3));
	//assert(!Circle1.LineToCircle(Line3));
	//assert(!Circle1.PointToCircle(Vector2(100.f)));
	////Box
	//assert(Box1.AABBToAABB(Box2)); 
	//assert(Box1.CircleToAABB(Circle2));
	//assert(Box1.LineToAABB(Line1)); 
	//assert(Box1.PointToAABB(Vector2(10.f)));
	//assert(!Box1.AABBToAABB(Box3));
	//assert(!Box1.CircleToAABB(Circle3));
	//assert(!Box1.LineToAABB(Line3)); 
	//assert(!Box1.PointToAABB(Vector2(100.f)));
	////Line
	//assert(Line1.LineToLine(Line2)); 
	//assert(Line1.PointToLine(Vector2(10.f, 2.f)));
	//assert(!Line1.PointToLine(Vector2(10.f)));
	//assert(!Line1.LineToLine(Line3));
	

	return;
}
