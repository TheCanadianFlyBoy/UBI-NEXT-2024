#include "stdafx.h"
#include "EngineProfiler.h"

void EngineProfiler::Render()
{
	Vector2 Initial = Vector2(20.f, APP_VIRTUAL_HEIGHT);

	for (std::string String : Output)
	{
		Initial -= Vector2(0.f, 20.f);
		Debug::DrawText(Initial, String);
	}

	Output.clear();
}