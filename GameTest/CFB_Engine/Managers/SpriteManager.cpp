#include "stdafx.h"
#include "SpriteManager.h"
//#include "../Resource/SpriteResource.h"


void SpriteManager::RegisterNewSprite(std::string InSpriteName, const char* FileName, unsigned int Columns, unsigned int Rows, unsigned int PoolCount)
{
    //Iterate to desired pool count
    for (int i = 0; i < PoolCount; i++) 
    {
        //Create a new shared pointer and push back to the appropriate vector
        SpriteResources[InSpriteName].push_back(std::shared_ptr<CSimpleSprite>(new CSimpleSprite(FileName, Columns, Rows)));
    }
}

/// <summary>
/// All purpose generation of sprites: will create a new sprite if provided with a filename or if there exists an existing 
/// </summary>
/// <param name="InSpriteName"></param>
/// <param name="FileName"></param>
/// <param name="Columns"></param>
/// <param name="Rows"></param>
/// <returns></returns>
std::shared_ptr<CSimpleSprite> SpriteManager::GenerateSprite(std::string InSpriteName)
{
    //Ensure we actually have this registered
    if (SpriteResources[InSpriteName].size() > 0)
    {
        //Create a copy
        std::shared_ptr<CSimpleSprite> Copy = std::make_shared<CSimpleSprite>(*SpriteResources[InSpriteName][0]);

        //Push back copy
        SpriteResources[InSpriteName].push_back(Copy);

        //Return
        return Copy;

    }

    //No sprite archetype as already generated, return null
    return nullptr;
}

/// <summary>
/// Looks for an available sprite of the given name
/// </summary>
/// <param name="InSpriteName">Sprite name</param>
/// <returns>Index in relevant vector or -1</returns>
int SpriteManager::GetAvailableSpriteIndex(std::string InSpriteName)
{
    //Make sure we actually have sprites in the vector
    if (SpriteResources[InSpriteName].size() > 0)
    {
        //Iterate
        for (int i = 0; i < SpriteResources[InSpriteName].size(); i++)
        {
            //If sprite is currently inactive, we can use it
            if (SpriteResources[InSpriteName][i].use_count() == 1)
            {
                //Return this index
                return i;
            }
        }

    }

    return -1;
}

/// <summary>
/// Gets an existing sprite of the given type, generates a new one, or returns nullptr in failure case
/// </summary>
/// <param name="InSpriteName">Name of sprite to find</param>
/// <param name="AutoInstantiate">Optional flag whether to create a new sprite or return null</param>
/// <returns>Sprite pointer or nullptr</returns>
std::shared_ptr<CSimpleSprite> SpriteManager::GetSprite(std::string InSpriteName, bool AutoInstantiate)
{
    //Check for index
    int SpriteIndex = GetAvailableSpriteIndex(InSpriteName);

    //If we have an existing sprite to use, we'll use that!
    if (SpriteIndex >= 0)
    {
        return std::shared_ptr<CSimpleSprite>(SpriteResources[InSpriteName][SpriteIndex]);
    }
    //Otherwise, we create a new one (unless told otherwise or we can't)
    else if (AutoInstantiate)
    {
        //If there has been at least one instantiation, we can generate a new one
        if (SpriteResources[InSpriteName].size() > 0)
        {
             return GenerateSprite(InSpriteName);
        }
    }



    return nullptr;
}

/// <summary>
/// Registers a new animation globally (affects ALL instances of this sprite)
/// </summary>
/// <param name="InSpriteName">Name of sprite</param>
/// <param name="AnimationID">ID to use</param>
/// <param name="AnimationSpeed">Speed of the animation</param>
/// <param name="Frames">IDs of frames to use</param>
void SpriteManager::RegisterAnimation(std::string InSpriteName, unsigned int AnimationID, float AnimationSpeed, const std::vector<int>& Frames)
{
    //Iterate
    for (auto SpritePointer : SpriteResources[InSpriteName])
    {
        //Pass to each instance
        SpritePointer->CreateAnimation(AnimationID, AnimationSpeed, Frames);
    }

}

/// <summary>
/// Gets the height of a given sprite type, without scaling
/// </summary>
/// <param name="InSpriteName">Name of sprite</param>
/// <returns>Sprite height or 0 if failure</returns>
float SpriteManager::GetSpriteHeight(std::string InSpriteName)
{
    //Check to make sure we actually have this sprite
    if (SpriteResources[InSpriteName].size() > 0)
    {
        //Return value
        return SpriteResources[InSpriteName][0]->GetHeight();
    }
    //Fail case, return 0.f
    return 0.0f;
}

/// <summary>
/// Gets the width of a given sprite type, without scaling
/// </summary>
/// <param name="InSpriteName">Name of sprite type</param>
/// <returns>Sprite width or 0 if failure</returns>
float SpriteManager::GetSpriteWidth(std::string InSpriteName)
{
    //Check to make sure we actually have this sprite
    if (SpriteResources[InSpriteName].size() > 0)
    {
        //Return value
        return SpriteResources[InSpriteName][0]->GetWidth();
    }
    //Fail case, return 0.f
    return 0.0f;
}
