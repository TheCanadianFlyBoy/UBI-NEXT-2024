#pragma once
/*
*	CFB Engine - UI Canvas
*	Container for UI elements, allows for passing of draw calls
*
*/

#include "../Object/Object.h"
#include "UIWidget.h"

#include <vector>
#include <memory>


class UICanvas : public Object
{
public:
	//Class Name
	inline virtual const char* GetObjectClassName() override { return GetStaticClassName(); }
	inline static const char* GetStaticClassName() { return "UICanvas"; }

	//Default constructor
	UICanvas() {};

    //Draw Call
    virtual void Render();
    virtual void Update(float DeltaTime);

public: // Methods
    //Widget Factory
    template <class Type>
    Type* AddWidget();

    //Widget Removal
    void RemoveWidget(UIWidget* InWidget);


protected: // Methods
	
    //Gets the index of an existing widget
	int GetIndexOfWidget(UIWidget* InWidget);
    //Gets the first index of a widget by type
	template <class Type>
	int GetIndexOfWidgetClass();

protected: // Members
	std::vector<std::unique_ptr<UIWidget>> Widgets; //TODO make a priority queue

};


template<class Type>
inline Type* UICanvas::AddWidget()
{
    //Check we have actually passed in a widget, otherwise this code will be broken
    assert((std::is_base_of <UIWidget, Type>()));

    //Create a unique pointer for mem mgmt
    Widgets.push_back(std::make_unique<Type>());

    //Return ptr to new object (we've already asserted so static cast is safe)
    return static_cast<Type*>(Widgets.back().get());
}

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
