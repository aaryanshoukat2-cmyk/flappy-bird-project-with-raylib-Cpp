#pragma once

#include "raylib.h"
#include <vector>
#include "GameTypes.h"

struct PipeSet
{
    Vector2 UpperPos;
    Vector2 LowerPos;

    Texture2D UpperPipe;
    Texture2D LowerPipe;
	
    Rectangle UpperCollisionBox;
    Rectangle BottomCollisionBox;

    Rectangle ScoreCollisionBox;
    float randomOffset;

    PipeSet(Texture2D texU, Texture2D texB)
    {
        UpperPipe = texU;
        LowerPipe = texB;
    }
};


struct PipeFunctions
{
    float timer;

    Texture2D upperTexture;
    Texture2D lowerTexture;

    std::vector<PipeSet> PipesCollection;

    PipeFunctions(Texture2D UpperTexture, Texture2D LowerTexture);

    PipeSet Create();

    void Update(GameState& state);
    void Render();
    void Unload();
    PipeFunctions();
};
