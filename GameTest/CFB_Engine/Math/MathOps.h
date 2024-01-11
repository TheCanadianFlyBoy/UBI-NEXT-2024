#pragma once
/*
*	CFB Engine - MathOps
*	A set of helper functions in their own name space that allow for 
*
*/

#include <math.h>
#include <random>
#include <chrono>
#include "../../App/app.h"

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
		return (x > 0) - (x < 0);
	}

	static inline float FRandom()
	{
		return 0.f;
	}
	

}

