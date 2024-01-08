#pragma once
/*
*	CFB Engine - UI Widget
*	Archetype for all UI Widgets
*
*/

#include "../Object/Object.h"

class UICanvas;

class UIWidget : public Object
{
public:
	//Class Name
	inline virtual const char* GetObjectClassName() override { return GetStaticClassName(); }
	inline static const char* GetStaticClassName() { return "UIWidget"; }

	//Constructor with optional Canvas argument
	UIWidget(UICanvas* InCanvas = nullptr) : Canvas(InCanvas)  {} ;
	
	//Draw Call
	virtual void Draw() = 0;

protected:

	//Reference to owning Canvas
	UICanvas* Canvas = nullptr;
	unsigned int ZOrder = 0;


};

/// <summary>
/// Basic Text Draw Widget
/// </summary>
class UIText : public UIWidget
{

};