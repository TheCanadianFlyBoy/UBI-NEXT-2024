#include "stdafx.h"
#include "UICanvas.h"
#include "UIWidget.h"

/// <summary>
/// Passes draw call to widgets
/// </summary>
void UICanvas::Draw()
{
    //Iterate
    for (UIWidget* Widget : Widgets)
    {
        //Pass draw call
        Widget->Draw();
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
        if (Widgets[i] == InWidget)
        {
            //Return value
            return i;
        }
    }

    //Fail case
    return -1;
}
