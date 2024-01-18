#include "stdafx.h"
#include "Collision.h"
#include <cassert>

bool CollisionBox::CircleToAABB(CollisionCircle& Circle)
{
	//Get edge
	float EdgeX = Circle.Position.x > Position.x ? GetMax().x : GetMin().x;
	float EdgeY = Circle.Position.y > Position.y ? GetMax().y : GetMin().y;
	//Distance
	float Distance = Vector2::Distance(Circle.Position, Vector2(EdgeX, EdgeY));
	//Check if in circle radius
	return Distance <= Circle.Radius;
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
	float DotProduct = (Position.x - Line.Start.x) * (Line.End.x - Line.Start.x) + (Position.y - Line.Start.y) * (Line.End.y - Line.Start.y) / pow(Line.GetLength(), 2);
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
	assert(Circle1.CircleToCircle(Circle2));
	assert(Circle1.LineToCircle(Line1));
	assert(Circle1.PointToCircle(Vector2(10.f)));
	assert(!Circle1.CircleToCircle(Circle3));
	assert(!Circle1.LineToCircle(Line3));
	assert(!Circle1.PointToCircle(Vector2(100.f)));
	//Box
	assert(Box1.AABBToAABB(Box2)); 
	assert(Box1.CircleToAABB(Circle2));
	assert(Box1.LineToAABB(Line1)); 
	assert(Box1.PointToAABB(Vector2(10.f)));
	assert(!Box1.AABBToAABB(Box3));
	assert(!Box1.CircleToAABB(Circle3));
	assert(!Box1.LineToAABB(Line3)); 
	assert(!Box1.PointToAABB(Vector2(100.f)));
	//Line
	assert(Line1.LineToLine(Line2)); 
	assert(Line1.PointToLine(Vector2(10.f, 2.f)));
	assert(!Line1.PointToLine(Vector2(10.f)));
	assert(!Line1.LineToLine(Line3));
	

	return;
}
