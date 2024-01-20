#pragma once
/*
*	CFB Engine - UI Manager
*	Handles UI canvas creation and access for multiple layers of UI.
*
*/

#include <vector>
#include <memory>

class UICanvas;

class UIManager
{
public:

	//Default Constructor
	UIManager();

protected:

	std::vector<std::unique_ptr<UICanvas>> Canvases;

};