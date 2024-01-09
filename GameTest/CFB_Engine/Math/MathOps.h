#pragma once
#include <math.h>
#include "../../App/app.h"


namespace MathOps {

	//How close a float needs to be for it to be "equal"
	const float float_epsilon = 0.0001f;

	static inline bool FloatEquals(const float a, const float b, const float epsilon = float_epsilon)
	{
		return fabsf(a - b) <= epsilon;
	}

	static inline float DegreesToRadians(const float degrees)
	{
		return float((degrees * PI / 180.f));
	}

	static inline float RadiansToDegrees(const float radians)
	{
		return (float)(radians / PI * 180.f);
	}

	static inline float FLerp(float a, float b, float delta)
	{
		return a + delta * (b - a);
	}

	static inline float FSign(float x)
	{
		return (x > 0) - (x < 0);
	}
}

