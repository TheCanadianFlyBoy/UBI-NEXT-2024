#pragma once
/*
*	CFB Engine - Audio Component
*	The base audio component for playing sounds in object context
*
*/

#include "Component.h"
#include "../../App/SimpleSound.h"

class CAudio : public Component
{
public:
	//Class Name
	inline virtual const char* GetObjectClassName() override { return GetStaticClassName(); }
	inline static const char* GetStaticClassName() { return "CAudio"; }

	CAudio(Entity* InEntity = nullptr, const char* InSoundFile = "") : Component(InEntity), SoundFile(InSoundFile) { };

public: // Methods
	//Sound setter
	inline void SetSound(const char* InSoundFile) { SoundFile = InSoundFile; };
	inline const char* GetSound() { return SoundFile; };

	//Play/Pause
	inline bool PlaySound() { return CSimpleSound::GetInstance().PlaySound(SoundFile, IsLooped); };
	inline bool StopSound() { return CSimpleSound::GetInstance().StopSound(SoundFile); };
	inline bool IsPlaying() { return CSimpleSound::GetInstance().IsPlaying(SoundFile); };

	//Looping
	inline bool GetLooping() { return IsLooped; };
	inline void SetLooping(bool InLooping) { IsLooped = InLooping; };


protected: // Members
	const char* SoundFile = "";

	bool IsLooped = false;

};