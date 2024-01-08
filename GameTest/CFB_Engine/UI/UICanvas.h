#pragma once
/*
*	CFB Engine - UI Canvas
*	Container for UI elements, allows for passing of draw calls
*
*/

#include "../Object/Object.h"

#include <vector>
#include <memory>

class UIWidget;

class UICanvas : public Object
{
public:
	//Class Name
	inline virtual const char* GetObjectClassName() override { return GetStaticClassName(); }
	inline static const char* GetStaticClassName() { return "UICanvas"; }

	//Default constructor
	UICanvas() {};

    //Draw Call
    virtual void Draw();




protected: // Methods
	
    //Gets the index of an existing widget
	int GetIndexOfWidget(UIWidget* InWidget);
    //Gets the first index of a widget by type
	template <class Type>
	int GetIndexOfWidgetClass();

protected: // Members
	std::vector<UIWidget*> Widgets; //TODO make a priority queue

};

template<class Type>
inline int UICanvas::GetIndexOfWidgetClass()
{
    //Iterate
    for (int i = 0; i < Widgets.size(); i++)
    {
        //Compare
        if (Widgets[i]->GetObjectClassName() == InWidget->GetObjectClassName())
        {
            //Return value
            return i;
        }
    }

    //Fail case
    return -1;
}
