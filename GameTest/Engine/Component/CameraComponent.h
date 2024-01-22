#pragma once
/*
*	 Engine - Camera Component
*	The base camera component for rendering the game through a given camera view
*
*/

#include "TransformComponent.h"

class Entity;
class Actor;

class CCamera : public CTransform
{
public:
	//Class Name
	inline virtual const char* GetObjectClassName() override { return GetStaticClassName(); }
	inline static const char* GetStaticClassName() { return "CCamera"; }

	//Default constructor with optional args
	CCamera(Entity* InEntity = nullptr) : CTransform(InEntity) {};

	//Update camera position
	void Update(float DeltaTime);

	//Getters
	inline Vector2 GetCameraOrigin() { return Origin; };
	inline Vector2 GetCameraDimensions() { return Dimensions; };

	//Setters
	inline void SetCameraDimensions(Vector2 InVector) { Dimensions = InVector; };
	//Target
	inline void SetTarget(Actor* InTarget) { TargetActor = InTarget; };
	inline Actor* GetTarget() { return TargetActor; }
	//Lag
	inline void SetCameraLag(float InLag) { CameraLag = InLag; }
	inline float GetCameraLag() { return CameraLag; }

	//Determines if there is a hard camera bound
	bool bCameraIsBound = false;

protected: // Members
	//Camera Origin - Centre point
	Vector2 Origin = Vector2(0.f);
	//Dimensions of the camera, default to app virtual size
	Vector2 Dimensions = Vector2(APP_VIRTUAL_WIDTH, APP_VIRTUAL_HEIGHT);
	//Speed of interpolation
	float CameraLag = 0.03f;
	//Hard bound for camera to keep player in view
	float CameraMaxDistance = 300.f;
	//Target for looking elsewhere
	Actor* TargetActor = nullptr;
	float TargetLingerTime = 4.f;
	float TargetLingerCounter = 0.f;




};