#pragma once
/*
*	CFB Engine - Sprite Component
*	Basic sprite component for provided sprite system. Uses transform component as a base to allow for offsets.
*	Wraps all basic API functions for ease of use.
*
*
*/

//Super
#include "TransformComponent.h"
#include "../../App/SimpleSprite.h"

class CSimpleSprite;
class CCamera;
class Entity;

class CSprite : public CTransform
{
public:
	enum class SpriteHeightAlignment
	{
		Bottom,
		Centre,
		Top
	};

public: 
	//Class Name
	inline virtual const char* GetObjectClassName() override { return GetStaticClassName(); }
	inline static const char* GetStaticClassName() { return "CSprite"; }

	//CONSTRUCTORS
	//Empty sprite component creation with optional args
	CSprite(Entity* InOwner = nullptr, std::shared_ptr<CSimpleSprite> InSprite = nullptr) { Owner = InOwner; Sprite = InSprite; };
	//Standard Constructor
	CSprite(Entity* InOwner, std::string InSpriteName);

	//Update call
	inline void Update(float DeltaTime) { Sprite->Update(DeltaTime); };
	//Draw call
	void Draw(CCamera* InCamera = nullptr);

public: //Methods
	//Setters
	inline void SetSprite(std::shared_ptr<CSimpleSprite> InSprite) { Sprite = InSprite; };
	//inline void GenerateSprite(const char* fileName, unsigned int columns = 1U, unsigned int rows = 1U) { Sprite = std::unique_ptr<CSimpleSprite>(new CSimpleSprite(fileName, columns, rows)); };

	//Animation wrappers
	inline void CreateAnimation(unsigned int AnimationID, float AnimationSpeed, const std::vector<int>& Frames) { Sprite->CreateAnimation(AnimationID, AnimationSpeed, Frames); };
	inline void SetAnimation(int AnimationID) { Sprite->SetAnimation(AnimationID); }
	inline unsigned int GetAnimationFrame() { return Sprite->GetFrame(); };

	//Scaling Wrappers
	inline float GetSpriteHeight() { return Sprite->GetHeight(); };
	inline float GetSpriteWidth()  { return Sprite->GetWidth();  };
	inline float GetSpriteScale()  { return Sprite->GetScale(); }; //TODO implement functionality

	//Colour
	inline void SetSpriteColour(float r, float g, float b) { Sprite->SetColor(r, g, b); };

	//Alignment
	inline void SetHeightAlignment(SpriteHeightAlignment Alignment) { HeightAlignment = Alignment; };
	inline SpriteHeightAlignment GetHeightAlignment() { return HeightAlignment; };
	

protected:
	std::shared_ptr<CSimpleSprite> Sprite;
	SpriteHeightAlignment HeightAlignment = SpriteHeightAlignment::Centre;

protected: //Methods
	inline void SetSpritePosition(Vector2 &InVector) { Sprite->SetPosition(InVector.x, InVector.y); };
	inline void SetSpriteRotation(float &InRotation) { Sprite->SetAngle(InRotation); };
	inline void UpdateSpriteLocation(Vector2& InVector, float& InRotation) { SetSpritePosition(InVector); SetSpriteRotation(InRotation); };


};