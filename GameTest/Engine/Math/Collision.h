#pragma once
/*
*	CFB Engine - Rigid Body Component
*	The archetype for all collision components in within the engine.
*
*/
#include "../Component/RigidBodyComponent.h"
#include "../Math/Vector2.h"
#include "../Utility/Debug.h"
#include "../Component/CameraComponent.h"

void CollisionUnitTest();

class Actor;

/// <summary>
/// A struct containing all the relevant info of a collision
/// </summary>
struct CollisionInfo
{
	//This
	Actor* ThisActor;
	CRigidBody* ThisBody;

	//Other
	Actor* OtherActor;
	CRigidBody* OtherBody;

	//Impact info
	Vector2 ImpactPoint;
	Vector2 Normal;

	//Penetration info
	Vector2 PenetrationVector;
	float PenetrationDepth;


};


struct CollisionPrimitive : public Object {
	//Class Name
	//inline virtual const char* GetObjectClassName() override { return GetStaticClassName(); }
	//inline static const char* GetStaticClassName() { return "CollisionPrimitive"; }

	//Constructor
	CollisionPrimitive(Vector2 InPosition = Vector2(0.f)) : Position(InPosition) {};


	//Common Properties
	Vector2 Position = Vector2(0.f);

	virtual void DebugDraw(CCamera* InCamera, Color3 InColor = Color3(1.f)) = 0;
	

};

struct CollisionBox : public CollisionPrimitive
{
	//Class Name
	inline virtual const char* GetObjectClassName() override { return GetStaticClassName(); }
	inline static const char* GetStaticClassName() { return "CollisionBox"; }

	//Constructor
	CollisionBox(Vector2 InPosition, Vector2 InBounds, bool Centred = false) : CollisionPrimitive(InPosition), Bounds(InBounds), PositionCentred(Centred) {};

	virtual void DebugDraw(CCamera* InCamera, Color3 InColor = Color3(1.f)) override { Debug::DrawRectangle(Position - InCamera->GetCameraOrigin(), Bounds, InColor, PositionCentred); };

	//Properties
	Vector2 Bounds = Vector2(0.f);
	bool PositionCentred = false;

	inline Vector2 GetCentre() { return PositionCentred ? Position : Position + Bounds / 2; }

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
			PositionCentred ? Position.x + (Bounds.x / 2) : Position.x + Bounds.x,
			PositionCentred ? Position.y + (Bounds.y / 2) : Position.y + Bounds.y
		);
	};

	//Checkers

	/// <summary>
	/// Checks for a point within the AABB
	/// </summary>
	/// <param name="Point">Point to check</param>
	/// <returns>Collision, true or false</returns>
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

		return (ThisMin.x >= OtherMin.x 
			 && ThisMin.x <= OtherMax.x 
			 && ThisMax.y >= OtherMin.y
			 && ThisMin.y <= OtherMax.y);

	}
	bool CircleToAABB(CollisionCircle& Circle, CollisionLine& CircleTrajectory, CollisionInfo& OutInfo);
	bool LineToAABB(CollisionLine& Line);

};

struct CollisionCircle : public CollisionPrimitive
{
	//Class Name
	inline virtual const char* GetObjectClassName() override { return GetStaticClassName(); }
	inline static const char* GetStaticClassName() { return "CollisionCircle"; }

	CollisionCircle(Vector2 InPosition, float InRadius) : CollisionPrimitive(InPosition), Radius(InRadius) {};
	
	virtual void DebugDraw(CCamera* InCamera, Color3 InColor = Color3(1.f)) override { Debug::DrawCircle(Position - InCamera->GetCameraOrigin(), Radius, 12, InColor); };

	//Properties
	float Radius = 0.f;


	//Methods
	//Getters
	inline bool PointToCircle(Vector2& Point) { return Point.DistanceFromSquared(Position) <= Radius; }
	inline bool CircleToCircle(CollisionCircle& Other) { return Position.DistanceFromSquared(Other.Position) < this->Radius + Other.Radius; }
	bool LineToCircle(CollisionLine& Line);

};

struct CollisionLine : public CollisionPrimitive 
{
	//Class Name
	inline virtual const char* GetObjectClassName() override { return GetStaticClassName(); }
	inline static const char* GetStaticClassName() { return "CollisionLine"; }

	//Constructor
	CollisionLine(Vector2 InStart, Vector2 InEnd, float InCollisionAccuracy = 0.2f, Vector2 InPosition = Vector2(0.f)) : CollisionPrimitive(InPosition), Start(InStart), End(InEnd), CollisionAccuracy(InCollisionAccuracy) {};

	virtual void DebugDraw(CCamera* InCamera, Color3 InColor = Color3(1.f)) override { Debug::DrawLine(Start - InCamera->GetCameraOrigin(), End + InCamera->GetCameraOrigin(), InColor); }

	//Properties
	Vector2 Start = Vector2(0.f);
	Vector2 End = Vector2(0.f);
	float CollisionAccuracy = 0.2f;

	//Methods
	//Getters
	inline const float GetLength() { return Start.DistanceFrom(End); }
	inline const float GetXSlope() { return End.x - Start.x; }
	inline const float GetYSlope() { return End.y - Start.y; }

	//Collision Checking
	
	/// <summary>
	/// Checks if there is a collision with the line at the given point
	/// </summary>
	/// <param name="Point">Point to check</param>
	/// <returns>Collision, true or false</returns>
	inline bool PointToLine(Vector2& Point) {
		//Get distances
		float PointDistanceStart = (Start).DistanceFrom(Point);
		float PointDistanceEnd = (End).DistanceFrom(Point);
		//Check if the line segment distances add up
		return (fabsf(PointDistanceStart + PointDistanceEnd) <= GetLength() + CollisionAccuracy);
	}

	/// <summary>
	/// Checks for collision with another line
	/// </summary>
	/// <param name="Other">Line to check</param>
	/// <returns>Collision, true or false</returns>
	inline bool LineToLine(CollisionLine& Other)
	{
		float Denominator = (Other.GetYSlope() * GetXSlope()) - (Other.GetXSlope() * GetYSlope());

		float A = ((Other.GetXSlope()) * (Start.y - Other.Start.y) - (Other.GetYSlope()) * (Start.x - Other.Start.x)) / Denominator;
		float B = ((GetXSlope()) * (Start.y - Other.Start.y) - (GetYSlope()) * (Start.x - Other.Start.x)) / Denominator;

		if (A >= 0 && A <= 1 && B >= 0 && B <= 1)
		{
			return true;
		};
		return false;
	}

	/// <summary>
	/// Checks for collision with another line
	/// </summary>
	/// <param name="Other">Line to check</param>
	/// <returns>Collision, true or false</returns>
	inline Vector2 GetLineToLineIntersection(CollisionLine& Other) {
		float Denominator = (Other.GetYSlope() * GetXSlope()) - (Other.GetXSlope() * GetYSlope());

		float A = ((Other.GetXSlope()) * (Start.y - Other.Start.y) - (Other.GetYSlope()) * (Start.x - Other.Start.x)) / Denominator;
		float B = ((GetXSlope()) * (Start.y - Other.Start.y) - (GetYSlope()) * (Start.x - Other.Start.x)) / Denominator;

		return Vector2(Start.x + (A * GetXSlope()), Start.y + (A * (GetYSlope())));
	}


	/// <summary>
	/// Gets the reflection vector of a collision
	/// </summary>
	/// <returns></returns>
	inline Vector2 GetReflection(Vector2 IncidentVector, Vector2 HitVector) 
	{
		//Get the normal to the hit vector
		//HitVector.

	}

};