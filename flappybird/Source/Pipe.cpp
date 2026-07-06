#include "Pipe.h"
#include "iostream"
#include "GameTypes.h"
PipeFunctions::PipeFunctions(Texture2D UpperTexture, Texture2D LowerTexture)
{
    upperTexture = UpperTexture;
    lowerTexture = LowerTexture;

    timer = 0;
    PipesCollection.reserve(6);
}


PipeSet PipeFunctions::Create()
{
    PipeSet newPipe(upperTexture, lowerTexture);


    newPipe.randomOffset = GetRandomValue(1,150);


    newPipe.UpperPos.x = 490;
    newPipe.LowerPos.x = 490;


    newPipe.UpperPos.y = -150 + newPipe.randomOffset;
    newPipe.LowerPos.y =  150 + newPipe.randomOffset;


    return newPipe;
}



void PipeFunctions::Update(GameState& state)
{
    //setting collide box position
    for(auto& pipe: PipesCollection){
    	pipe.UpperCollisionBox = {pipe.UpperPos.x + 150,pipe.UpperPos.y - 120,100.0f,400.0f};
    	pipe.BottomCollisionBox = {pipe.LowerPos.x + 150,pipe.LowerPos.y + 120,100.0f,400.0f};
	pipe.ScoreCollisionBox = {pipe.UpperPos.x + pipe.UpperCollisionBox.width + 50,(pipe.UpperPos.y + pipe.UpperCollisionBox.height) - 120,1,150};
    }
    timer += GetFrameTime();
 if(state == GameState::playing){
    if(timer >= 2.0f)
    {

        PipesCollection.push_back(Create());

        timer = 0;

    }
 }


    //preventing erasing in empty array
    if(!PipesCollection.empty())
    {

        if(PipesCollection[0].UpperCollisionBox.x <= -200)
        {

            PipesCollection.erase(PipesCollection.begin());


        }

    }
    //moving pipes
	   for(auto& pipe : PipesCollection)
    {

        	pipe.UpperPos.x -= 2;
        	pipe.LowerPos.x -= 2;

    }
}


		
void PipeFunctions::Render()
{
    for(auto& pipe : PipesCollection)
    {
        DrawTexturePro(
            pipe.UpperPipe,
            {0,0,(float)pipe.UpperPipe.width,(float)pipe.UpperPipe.height},
            {pipe.UpperPos.x, pipe.UpperPos.y,400,400},
            {0,0},
            0,
            RAYWHITE
        );


        DrawTexturePro(
            pipe.LowerPipe,
            {0,0,(float)pipe.LowerPipe.width,(float)-pipe.LowerPipe.height},
            {pipe.LowerPos.x, pipe.LowerPos.y,400,400},
            {0,0},
            0,
            RAYWHITE
        );
		std::cout<<pipe.UpperPos.x<<" "<<pipe.UpperPipe.width<<std::endl;
    }
}



