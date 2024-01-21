#include "stdafx.h"
#include "UICanvas.h"
#include "UIWidget.h"

/// <summary>
/// Passes draw call to widgets
/// </summary>
void UICanvas::Render()
{
    //Iterate
    for (auto &Widget : Widgets)
    {
        //Pass draw call
        Widget->Render();
    }

}

/// <summary>
/// Wake all widgets
/// </summary>
void UICanvas::OnBegin()
{
    for (auto& Widget : Widgets)
    {
        Widget->OnBegin();
    }
}

void UICanvas::Update(float DeltaTime)
{
    for (auto& Widget : Widgets)
    {
        if (Widget && Widget->Active)
            Widget->Update(DeltaTime);
    }
}

/// <summary>
/// Clear all for shutdown
/// </summary>
void UICanvas::Shutdown()
{
    Object::Shutdown();

    for (auto& Widget : Widgets)
    {
        Widget->Shutdown();
    }
}


/// <summary>
/// Removes a given widget from the canvas
/// </summary>
/// <param name="InWidget"></param>
void UICanvas::RemoveWidget(UIWidget* InWidget)
{
    //Size check
    if (Widgets.size() > 0)
    {
        //Iterate
        for (int i = 0; i < Widgets.size(); i++)
        {
            //Get the current widget
            UIWidget* CurrentWidget = Widgets[i].get();

            //Check if we have a match
            if (CurrentWidget == InWidget)
            {
                //match, remove
                Widgets.erase(Widgets.begin() + i); //TODO erase remove?
            }

        }
    }
}

/// <summary>
/// Gets the index of an existing widget or returns -1
/// </summary>
/// <param name="InWidget">Pointer to Widget</param>
/// <returns>Index of widget or -1 in fail case</returns>
int UICanvas::GetIndexOfWidget(UIWidget* InWidget)
{
    //Iterate
    for (int i = 0; i < Widgets.size(); i++)
    {
        //Compare
        if (Widgets[i].get() == InWidget)
        {
            //Return value
            return i;
        }
    }

    //Fail case
    return -1;
}
