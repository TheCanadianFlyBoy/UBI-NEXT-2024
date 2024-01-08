#pragma once
#include <math.h>


namespace MathOps {
	//Moderately accurate PI value
	#define PI 3.141592//65358979

	//How close a float needs to be for it to be "equal"
	const float float_epsilon = 0.0001f;

	inline bool float_equals(const float a, const float b, const float epsilon = float_epsilon)
	{
		return fabsf(a - b) <= epsilon;
	}

	inline float degreesToRadians(const float degrees)
	{
		return float((degrees * PI / 180.f));
	}

	inline float radiansToDegrees(const float radians)
	{
		return (float)(radians / PI * 180.f);
	}

	inline float flerp(float a, float b, float delta)
	{
		return a + delta * (b - a);
	}
}

