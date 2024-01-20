#include "stdafx.h"
#include "MathOps.h"
#include "Vector2.h"

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
