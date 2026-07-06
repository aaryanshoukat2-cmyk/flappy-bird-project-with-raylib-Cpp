#include "Game.h"
#include "bird.h"
#include "Pipe.h"
#include "iostream"
#include "Collision.h"
#include "vector"

Game::Game(){
	state = GameState::started;
	score = 0;
	WLstate = playerState::none;
	flappyFont = LoadFont("../Textures/flappybirdy/FlappyBirdy.ttf");
	button = {160,250,180,60};
	IsPaused = false;
}

void Game::ScoreIncrease(){
	//score cap
	if(score < 0){
		score = 0;
	}
	if(score >= 999){
		WLstate = playerState::won;
	}
	++score;
}
int Game::GetScore(){
	return score;
}
void Game::StartScreen(){
	DrawTextPro(
    flappyFont, 
    "Flappy Bird", 
    (Vector2){ 250.0f, 180.0f }, 
    (Vector2){ MeasureTextEx(flappyFont, "Flappy Bird", 60.0f, 2.0f).x / 2.0f, MeasureTextEx(flappyFont, "Flappy Bird", 60.0f, 2.0f).y / 2.0f }, 
    0.0f, 
    60.0f, 
    2.0f, 
    BLACK
);
	
	DrawRectangleRoundedLinesEx((Rectangle)button, 0.4f, 16, 2.0f, BLACK);
	DrawText("PLAY",185,255,50,BLACK);
}

void Game::WinScreen(){
	DrawText("You Win!",230,250,50,BLACK);

}

void Game::ScoreDisplayer(){
	DrawText(TextFormat("%03i",GetScore()),230,0,50,BLACK);
}
void Game::PauseCheck(){
if(state == GameState::playing || state == GameState::paused){
	if(IsKeyPressed(KEY_ESCAPE) && IsPaused == false){
		state = GameState::paused;
		IsPaused = true;
	}
       else if(IsKeyPressed(KEY_ESCAPE) && IsPaused == true){
		state = GameState::playing;
		IsPaused = false;
	}
}
if(state == GameState::started){}
	
}


void Game::PauseScreen(){
		DrawTextPro(
    flappyFont, 
    "PAUSED", 
    (Vector2){ 250.0f, 180.0f }, 
    (Vector2){ MeasureTextEx(flappyFont, "PAUSED", 60.0f, 2.0f).x / 2.0f, MeasureTextEx(flappyFont, "PAUSED", 60.0f, 2.0f).y / 2.0f }, 
    0.0f, 
    60.0f, 
    2.0f, 
    BLACK
);

	
	
}

void Game::RestartScreen(PipeFunctions& pipeF,bird& player){
	pipeF.PipesCollection.clear();
   	player.pos = {250,250};	
	player.velocityY = 0;
	Rectangle restartButton = {160,250,180,60};
		DrawTextPro(
    flappyFont, 
    "Game Over", 
    (Vector2){ 250.0f, 180.0f }, 
    (Vector2){ MeasureTextEx(flappyFont, "Game Over", 60.0f, 2.0f).x / 2.0f, MeasureTextEx(flappyFont, "Game Over", 60.0f, 2.0f).y / 2.0f }, 
    0.0f, 
    60.0f, 
    2.0f, 
    BLACK
);
	
	DrawRectangleRoundedLinesEx((Rectangle)restartButton, 0.4f, 16, 2.0f, BLACK);
	DrawText("Restart",170,255,40,BLACK);
	if(CheckCollisionPointRec(GetMousePosition(),restartButton) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
		state = GameState::playing;
		player.state = birdState::alive;
	}

}

void Game::ScoreUpdate(PipeSet& pipe,bird& player){
	if(player.pos.x == (pipe.UpperPos.x + pipe.UpperCollisionBox.width) && player.pos.y > 0 && player.pos.y < 500){
		ScoreIncrease();
		std::cout<<GetScore()<<std::endl;
		std::cout<<"score increased by 1"<<std::endl;
	}
	if(WLstate == playerState::won || state == GameState::ended){
		score = 0;
	}
}

void Game::ButtonListener(bird& player){
		if(CheckCollisionPointRec(GetMousePosition(),button) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
			state = GameState::playing;
			player.state = birdState::alive;
	}
}

void Game::InputStateManager(bird& player,PipeFunctions& pipeF){
	if(state == GameState::playing)
		player.Input();
		PauseCheck();
	if(state == GameState::started)
		ButtonListener(player);


}

void Game::UpdateStateManager(bird& player, PipeFunctions& pipeF,CollisionCheck& check){
		if(state == GameState::playing){	
		player.Update();
		pipeF.Update(state);
	
		
		for(auto& pipe:pipeF.PipesCollection){
			check.UpdatePipeCollision(player.collisionBox,pipe.UpperCollisionBox,WLstate,state);
			check.UpdatePipeCollision(player.collisionBox,pipe.BottomCollisionBox,WLstate,state);
			check.UpdateOutOfBounds(player.pos,state,WLstate);
			ScoreUpdate(pipe,player); 
		
	}
	}
		if(state == GameState::ended){
			player.state = birdState::dead;
		}
}

void Game::RenderStateManager(bird& player,PipeFunctions& pipeF){
	if(state == GameState::started && player.state == birdState::none){
		StartScreen();
	}
	if(state == GameState::paused && player.state == birdState::alive){
	//pause
		PauseScreen();
	}
	if(state == GameState::ended && player.state == birdState::dead){
	//restart screen
		RestartScreen(pipeF,player);
	}
	
	 if(player.state == birdState::alive){
	 	if(state == GameState::playing){
			if(WLstate == playerState::won){
				WinScreen();
			}
				player.Render();
				pipeF.Render();
			if(WLstate != playerState::won){
				ScoreDisplayer();
			}
		}
		if(state == GameState::paused){
			PauseScreen();
		}	
	 }
	 
	 
	


}
Game::~Game(){
	UnloadFont(flappyFont);
}
