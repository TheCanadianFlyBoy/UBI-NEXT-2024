#pragma once
/*
*	CFB Engine - UI Widget
*	Archetype for all UI Widgets
*
*/

#include "../App/app.h"
#include "../Object/Object.h"
#include "../Math/Vector2.h"
#include "../Math/Vector3.h"
#include "../Math/Collision.h"

#include <functional>

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
	virtual void Render() = 0;

	inline void SetPosition(Vector2& InVector) { Position = InVector; }
	inline Vector2 GetPosition()			   { return Position; }

	virtual void Callback() {};

protected:

	//Reference to owning Canvas
	UICanvas* Canvas = nullptr;

	//Position in screen space
	Vector2 Position = Vector2(0.f);

	//Z Order
	unsigned int ZOrder = 0;


};

/// <summary>
/// Basic Text Draw Widget
/// </summary>
class UIText : public UIWidget
{
public: // Methods
	//Setters
	inline void SetColor(Color3 InColor) { TextColor = InColor; };
	inline void SetText(std::string InString) { Text = InString; };
	//Getters
	inline Color3 GetColor() { return TextColor; };
	inline std::string GetText() { return Text; };
	//Draw Override
	virtual void Render() override {

		App::Print(Position.x, Position.y, Text.c_str(), TextColor.r, TextColor.g, TextColor.b);

	}


protected: // Properties
	Color3 TextColor = Color3(1.f);
	std::string Text = "";

};

/// <summary>
/// Basic Text with border
/// </summary>
class UITextBox : public UIText
{
public:
	//Box dimensions
	inline void SetDimensions(Vector2 InVector) { Dimensions = InVector; }
	inline Vector2 GetDimensions() { return Dimensions; }
	//Line Thickness
	inline void SetLineThickness(float InThickness) { LineThickness = InThickness; }
	inline float GetLineThickness() { return LineThickness; }
	//Box Color
	inline void SetBoxColor(Color3 InColor) { BoxColor = InColor; }
	inline Color3 GetBoxColor() { return BoxColor; }

	virtual void Render() override
	{
		Vector2 TopLeft			= Vector2(Position.x - (Dimensions.x / 2), Position.y - (Dimensions.y / 2));
		Vector2 TopRight		= Vector2(Position.x + (Dimensions.x / 2), Position.y - (Dimensions.y / 2));
		Vector2 BottomLeft		= Vector2(Position.x - (Dimensions.x / 2), Position.y + (Dimensions.y / 2));
		Vector2 BottomRight		= Vector2(Position.x + (Dimensions.x / 2), Position.y + (Dimensions.y / 2));

		//Draw box
		App::DrawLine(TopLeft.x, TopLeft.y, TopRight.x, TopRight.y, BoxColor.r, BoxColor.g, BoxColor.b); //TOP
		App::DrawLine(TopRight.x, TopRight.y, BottomRight.x, BottomRight.y, BoxColor.r, BoxColor.g, BoxColor.b); //RIGHT
		App::DrawLine(BottomRight.x, BottomRight.y, BottomLeft.x, BottomLeft.y, BoxColor.r, BoxColor.g, BoxColor.b); //BOTTOM
		App::DrawLine(BottomLeft.x, BottomRight.y, TopLeft.x, TopLeft.y, BoxColor.r, BoxColor.g, BoxColor.b); //LEFT

		//Super
		UIText::Render();

	}
protected:

	Vector2 Dimensions = Vector2(0.f);
	float LineThickness = 1.f;
	Color3 BoxColor = Color3(1.f);
};

class UIButton : public UITextBox
{
public:

	//Update override
	virtual void Update(float DeltaTime) override {
		//Setup the collision
		AABB.Position = Position;
		AABB.Bounds = Dimensions;
		//Get mouse
		float MouseX; float MouseY;
		App::GetMousePos(MouseX, MouseY);

		//Reset box color
		BoxColor = ButtonColor;
		//If mouse is over box...
		if (AABB.PointToAABB(Vector2(MouseX, MouseY)))
		{
			//Set the color
			BoxColor = MouseOverColor;
			//If we click...
			if (App::GetController().CheckButton(XINPUT_GAMEPAD_A) || App::IsKeyPressed(VK_LBUTTON))
			{
				//Set color
				BoxColor = ClickedColor;
				Callback();
			}

		}

		UITextBox::Render();

	}

	Color3 ButtonColor = Color3(1.f);
	Color3 MouseOverColor = Color3(0.3f, 0.5f, 0.7f);
	Color3 ClickedColor = Color3(0.2f, 0.2f, 0.2f);

	inline  CollisionBox& GetCollisionBox() { return AABB; };

protected: // Members
	CollisionBox AABB = CollisionBox(Position, Dimensions,true);
	bool bMouseOver = false;
	bool bClicked = false;
};