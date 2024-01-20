#include "stdafx.h"

#include "Debug.h"
#include "EngineProfiler.h"

void Debug::PrintLine(std::string InText)
{
	EngineProfiler::GetInstance()->Output.push_back(InText);
}