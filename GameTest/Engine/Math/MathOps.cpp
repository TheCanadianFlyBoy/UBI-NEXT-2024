#include "stdafx.h"
#include "MathOps.h"
#include "Vector2.h"

Vector2 MathOps::VectorLerp(::Vector2 A, ::Vector2 B, float Delta)
{
	A.x = FLerp(A.x, B.x, Delta);
	A.y = FLerp(A.y, B.y, Delta);
	return A;
}

std::vector<Vector2> MathOps::CreateCirclePoints(float Radius, int SegmentCount)
{
	std::vector<Vector2> OutVector;

	for (float Angle = 0.f; Angle <= 2 * PI; Angle += 2 * PI / SegmentCount)
	{
		Vector2 NewPosition = Vector2(cosf(Angle) * Radius, sinf(Angle) * Radius);
		OutVector.push_back(NewPosition);
	}

	return OutVector;
}
