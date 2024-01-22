#pragma once
/*
*	CFB Engine - Engine Profiler
*	Components for the engine to internally display debug info realtime
*
*/

#include "../../App/app.h"
#include "../Math/MathOps.h"
#include "../Math/Vector2.h"
#include "../Math/Vector3.h"

#include "Debug.h"

  //////////////////////////////////////////////////////////////////////////////////////////////////////
 ///									Header Start												///
//////////////////////////////////////////////////////////////////////////////////////////////////////
class EngineProfiler
{
	DECLARE_SINGLE(EngineProfiler);
public:
	std::vector<std::string> Output;

	void Render();
};