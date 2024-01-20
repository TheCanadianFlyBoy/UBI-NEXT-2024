#pragma once
/*
*	CFB Engine - MathOps
*	A set of helper functions in their own name space that allow for 
*
*/

#include <math.h>
#include <random>
#include <chrono>

#include <cassert>

#include "../../App/app.h"

class Vector2;

namespace MathOps {

	//How close a float needs to be for it to be "equal"
	const float FloatEpsilon = 0.0001f;

	static inline bool FloatEquals(const float a, const float b, const float epsilon = FloatEpsilon)
	{
		return fabsf(a - b) <= epsilon;
	}

	static inline float DegreesToRadians(const float InDegrees)
	{
		return float((InDegrees * PI / 180.f));
	}

	static inline float RadiansToDegrees(const float InRadians)
	{
		return (float)(InRadians / PI * 180.f);
	}

	static inline float FLerp(float a, float b, float Delta)
	{
		return a + Delta * (b - a);
	}

	static inline float FSign(float x)
	{
		return float((x > 0.f) - (x < 0.f));
	}

	static inline float FRandom()
	{
		return 0.f;
	}
	
	static inline float FClamp(float Value, float Min, float Max)
	{
		return std::max<float>(Min, std::min<float>(Max, Value));
	}

	std::vector<Vector2> CreateCirclePoints(float Radius, int SegmentCount);

	inline float CalculateCircleSegment(float Radius, float Height)
	{
		if (Radius < Height) return 0;
		float area = Radius * Radius * acosf(1 - (Height / Radius)) - ((Radius - Height) * sqrtf(Radius * Radius - ((Radius - Height) * (Radius - Height))));
		assert(!isnan(area));
		return area;
	}

}

