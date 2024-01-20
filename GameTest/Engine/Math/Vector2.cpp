#include "stdafx.h"
#include "Vector2.h"

bool Vector2::Test()
{
	Vector2 a(2, 2);
	Vector2 b(4, 4);

	a.Set(4, 4);
	if (a != b) return false;
	a.Set(2, 2);
	a *= a;
	if (a != b) return false;
	if (a != b) return false;
	a.Set(2, 2);
	a *= 2;
	if (a != b) return false;
	a.Set(2, 2);
	a = a * 2;
	if (a != b) return false;
	a.Set(2, 2);
	a += a;
	if (a != b) return false;
	a.Set(2, 2);
	a -= -a;
	if (a != b) return false;
	a.Set(2, 2);

	return true;
}
