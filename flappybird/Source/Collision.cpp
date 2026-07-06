#include "raylib.h"
#include "Collision.h"
#include "bird.h"
#include "Game.h"
#include "iostream"
void CollisionCheck::UpdatePipeCollision(Rectangle& player,Rectangle& Pipe/*,Rectangle& ScoreBox,Rectangle& playerScoreBox,*/,playerState& WLstate,GameState& state){
	if(CheckCollisionRecs(player,Pipe)){
		//change Game State
		if(WLstate != playerState::won){
	 	WLstate  = playerState::lost;
		state = GameState::ended;	
		std::cout<<"Collided with Pipe"<<std::endl;
		}
		}
//	if(CheckCollisionRecs(playerScoreBox,ScoreBox)){
		//increase score
	//	std::cout<<"Score Increased by 1"<<std::endl;
	
//	}
	else{}
}
void CollisionCheck::UpdateOutOfBounds(Vector2 pos,GameState& state, playerState& WLstate){
	if((pos.y > 500 || pos.y < 0) && WLstate != playerState::won){
		WLstate = playerState::lost;
		state = GameState::ended;
	}
}
