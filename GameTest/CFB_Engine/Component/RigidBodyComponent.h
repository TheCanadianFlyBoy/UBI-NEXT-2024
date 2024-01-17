#pragma once
/*
*	CFB Engine - Rigid Body Component
*	The archetype for all collision components in within the engine.
*
*/

#include "Component.h"
#include "../Math/Vector2.h"

class Entity;

/// <summary>
/// A struct containing all the relevant info of a collision
/// </summary>
struct CollisionInfo
{
	//This
	Entity* This;
	CRigidBody* ThisBody;

	//Other
	Entity* Other;
	CRigidBody* OtherBody;

	//Impact info
	Vector2 ImpactPoint;
	Vector2 Normal;


};

struct CollisionBox
{
	//Properties
	Vector2 Position = Vector2(0.f);
	Vector2 Bounds = Vector2(0.f);
	bool PositionCentred = false;
		//Methods
	//Getters
	inline Vector2 GetMin() const {
		return Vector2(
			PositionCentred ? Position.x - (Bounds.x / 2) : Position.x,
			PositionCentred ? Position.y - (Bounds.y / 2) : Position.y
		);
	};
	inline Vector2 GetMax() const {
		return Vector2(
			PositionCentred ? Position.x + (Bounds.x / 2) : Position.x,
			PositionCentred ? Position.y + (Bounds.y / 2) : Position.y
		);
	};

	//Checkers
	inline bool PointToAABB(Vector2& Point) const {
		//Get mins and maxes	
		Vector2 Min = GetMin();
		Vector2 Max = GetMax();
		//Return result of check
		return (Point.x >= Min.x && Point.x <= Max.x && Point.y >= Min.y && Point.y <= Max.y);

	};
	inline bool AABBToAABB(CollisionBox& Other) const {
		//Get mins and maxes
		Vector2 ThisMin = GetMin();
		Vector2 ThisMax = GetMax();
		Vector2 OtherMin = Other.GetMin();
		Vector2 OtherMax = Other.GetMax();

		return (ThisMin.x >= OtherMin.x && ThisMax.x <= OtherMax.x && 
			ThisMin.y >= OtherMin.y && ThisMax.y <= OtherMax.y);

	}
	inline bool CircleToAABB(CollisionCircle& Circle) {
		//Get edge
		float EdgeX = Circle.Position.x > Position.x ? GetMax().x : GetMin().x;
		float EdgeY = Circle.Position.y > Position.y ? GetMax().y : GetMin().y;
		//Distance
		float Distance = Vector2::Distance(Circle.Position, Vector2(EdgeX, EdgeY));
		//Check if in circle radius
		return Distance <= Circle.Radius;
	};

};

struct CollisionCircle
{
	//Properties
	Vector2 Position = Vector2(0.f);
	float Radius = 0.f;

		//Methods
	//Getters
	inline bool PointToCircle(Vector2& Point) { return Point.DistanceFromSquared(Position) <= Radius; }
	inline bool CircleToCircle(CollisionCircle& Other) { return Position.DistanceFromSquared(Other.Position) < this->Radius + Other.Radius; }
	inline bool LineToCircle(CollisionLine& Line)
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
	};

};

struct CollisionLine {
	//Properties
	Vector2 Start = Vector2(0.f);
	Vector2 End = Vector2(0.f);
	float CollisionAccuracy = 0.2f;

	//Methods
	//Getters
	inline const float GetLength() { return Start.DistanceFrom(End); }
	inline const float GetXSlope() { return End.x - Start.x; }
	inline const float GetYSlope() { return End.y - Start.y; }

	inline bool PointToLine(Vector2& Point) {
		//Get distances
		float PointDistanceStart = Start.DistanceFrom(Point);
		float PointDistanceEnd = End.DistanceFrom(Point);
		//Check if the line segment distances add up
		return (fabsf(PointDistanceStart + PointDistanceEnd) <= GetLength() + CollisionAccuracy);
	}
	inline bool LineToLine(CollisionLine& Other)
	{
		//TODO
	}

};

class CRigidBody : public Component
{
public: //Properties
	//Class Name
	inline virtual const char* GetObjectClassName() override { return GetStaticClassName(); }
	inline static const char* GetStaticClassName() { return "CRigidBody"; }

	//Constructor with optional args
	CRigidBody(Entity* InEntity = nullptr) : Component(InEntity) {};

	//Static check for checking two collisions TODO
	//inline static bool CheckCollision(CRigidBody* This, CRigidBody* Other) { This->GetBodyCollision(Other); }

protected: // Methods

	//Gets if there is a collision between two bodies
	virtual bool GetBodyCollision(CRigidBody* Other, CollisionInfo& OutHitInfo) = 0;

	

};