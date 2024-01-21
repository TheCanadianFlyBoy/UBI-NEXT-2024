#pragma once
/*
*	CFB Engine 
*	Instance of the engine, responsible for creating and managing global managers
*
*/

#include <memory>
#include <vector>
#include <random>

#include "World/World.h"

#define ENGINE_DEBUG_MODE true
#define FIXED_UPDATE_FREQUENCY 0.2f

//class SpriteManager;
class UIManager;

#define ENGINE EngineCore::GetInstance()

class EngineCore
{
	DECLARE_SINGLE(EngineCore); // Declare this as a singleton system (only one instance ever)

public: // Methods
	
	//Initializes member elements
	void Initialize();

	void Update(float DeltaTime);
	void LateUpdate(float DeltaTime);
	void Render();
	void Shutdown();

	//Returns current world
	inline World* GetCurrentWorld() { return CurrentWorld; }
	void LoadWorld(World* InWorld);
	void LoadWorld(std::string Name);
	//Deletes a world
	void DeleteWorld(World* InWorld);

	//Returns Sprite Manager
	inline SpriteManager* GetSpriteManager() { return SpriteManager::GetInstance(); }


	//Easy clearing of global UI
	inline void ClearGlobalCanvases() { 
		for (auto& Widget : GlobalCanvases)
		{
			Widget->Shutdown();
		}
		GlobalCanvases.clear(); }

public: //Factory Constructors

	template <class Type>
	Type* CreateWorld(std::string Name);

	template <class Type>
	Type* CreateGlobalWidget(UICanvas* InCanvas = nullptr);

	template <class Type>
	Type* CreateGlobalCanvas();

protected: // Members


	//Creates an MT for random usage
	std::mt19937 MersenneTwister = std::mt19937(unsigned int(time(NULL)));

	float FixedUpdateTimer = 0.f;

	//Active world
	World* CurrentWorld = nullptr;

	//World Vector
	std::map<std::string, std::unique_ptr<World>> Worlds; // TODO MAP for saving names
	//Persistent Canvases
	std::vector <std::unique_ptr<UICanvas>> GlobalCanvases;

public: //Helpers
	//Mouse Position
	Vector2 GetMouseScreenPosition();
	Vector2 GetMouseWorldPosition();
	//Thumbstick helpers
	inline Vector2 GetLeftStick() { return Vector2(App::GetController().GetLeftThumbStickX(), App::GetController().GetLeftThumbStickY()); }
	inline Vector2 GetRightStick() { return Vector2(App::GetController().GetRightThumbStickX(), App::GetController().GetRightThumbStickY()); }
	//DPad
	inline Vector2 GetDPad()	{ return Vector2(
		float(App::GetController().CheckButton((APP_PAD_EMUL_DPAD_RIGHT) - App::GetController().CheckButton(APP_PAD_EMUL_DPAD_LEFT))),
		float(App::GetController().CheckButton((APP_PAD_EMUL_DPAD_DOWN) - App::GetController().CheckButton(APP_PAD_EMUL_DPAD_UP)))
		); }
	//Shorthand for buttons
	inline bool CheckButton(int ButtonCode, bool CheckPressed = false) { return App::GetController().CheckButton(ButtonCode, CheckPressed); }

	//Camera getter with null check
	inline CCamera* GetActiveWorldCamera() { return GetCurrentWorld() ? GetCurrentWorld()->GetActiveCamera() : nullptr; }

	//Random
	inline float RandRangeF(float Min, float Max)
	{
		std::uniform_real_distribution<> Distribution(Min, Max);

		return float(Distribution(MersenneTwister));

	}

	inline float RandF()
	{
		std::uniform_real<> Generator(FLT_MIN, FLT_MAX);

		return float(Generator(MersenneTwister));
	}


};

/// <summary>
/// Constructs a new world of the given type
/// </summary>
/// <typeparam name="Type"></typeparam>
/// <returns></returns>
template<class Type>
inline Type* EngineCore::CreateWorld(std::string Name)
{
	//Check we have actually passed in an entity, otherwise this code will be broken
	assert((std::is_base_of < World, Type>()));

	//Create a unique pointer for mem mgmt
	Worlds[Name] = (std::make_unique<Type>(this));

	//Return ptr to new object
	return static_cast<Type*>(Worlds[Name].get());
}

/// <summary>
/// Creates a widget
/// </summary>
/// <typeparam name="Type"></typeparam>							 //TODO fix these descs
/// <param name="InCanvas"></param>
/// <returns></returns>
template<class Type>
inline Type* EngineCore::CreateGlobalWidget(UICanvas* InCanvas)
{
	//Check we have actually passed in an entity, otherwise this code will be broken
	assert((std::is_base_of <UIWidget, Type>()));

	//Create a unique pointer for mem mgmt
	return InCanvas->AddWidget<Type>();

}


/// <summary>
/// Creates a canvas 
/// </summary>
/// <typeparam name="Type"></typeparam>
/// <returns></returns>
template<class Type>
inline Type* EngineCore::CreateGlobalCanvas()
{
	//Check we have actually passed in an entity, otherwise this code will be broken
	assert((std::is_base_of <UICanvas, Type>()));

	//Create a unique pointer for mem mgmt
	GlobalCanvases.push_back(std::make_unique<Type>());

	//Return ptr to new object (we've already asserted so static cast is safe)
	return static_cast<Type*>(GlobalCanvases.back().get());
}