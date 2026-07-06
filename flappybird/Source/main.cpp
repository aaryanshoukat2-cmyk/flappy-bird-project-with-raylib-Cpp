#include "raylib.h"
#include "bird.h"
#include "Game.h"
#include "Pipe.h"
#include "Collision.h"
#include "iostream"
#include "GameTypes.h"
const short MAX_HEIGHT = 500;
const short MAX_WIDTH  = 500;
const short MAX_FPS    = 60;
void Input(bird& player,Game& game,PipeFunctions& pipeF){
	game.InputStateManager(player,pipeF);
}


void Update(bird& player,PipeFunctions& pipeF,CollisionCheck& check,Game& game){
		game.UpdateStateManager(player,pipeF,check);
	}

void Render(bird& player,PipeFunctions& pipeF,Game& game){
		game.RenderStateManager(player,pipeF);	
}

void RunGame(){
	InitWindow(MAX_WIDTH,MAX_HEIGHT,"flappy bird");
	SetExitKey(KEY_NULL);
	SetTargetFPS(MAX_FPS);
	//creating & loading variables
	Texture2D uTex = LoadTexture("../Textures/pipe.png");Texture2D bTex = LoadTexture("../Textures/pipe.png");
	PipeFunctions pipe(uTex,bTex);
	
	Game game;
	CollisionCheck check;
	bird player;
	
	// end of creation
	while(!WindowShouldClose()){
		Input(player,game,pipe);
		Update(player,pipe,check,game);
		BeginDrawing();
			ClearBackground(RAYWHITE);
			Render(player,pipe,game);
		EndDrawing();
	}
	CloseWindow();
}
int main(){
	RunGame();
	return 0;
}
