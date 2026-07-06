#include "raylib.h"
#include "bird.h"
#include "Pipe.h"
#include "Game.h"
#include "iostream"
bird::bird(){
	Create();
        state = birdState::none;
}
void bird::Jump(){
	velocityY = -8.0f;
}
void bird::Create(){
		pos = {250,250};	
		gravity = 0.5f;
		velocityY = 0.0f;
		bird_texture = LoadTexture("../Textures/bird.png.png");
}
void bird::Input(){
		if(IsKeyPressed(KEY_SPACE)){
			Jump();
		}	
}	
	void bird::Update(){
			velocityY += gravity;
			pos.y += velocityY;
			collisionBox.x = pos.x;
			collisionBox.y = pos.y;
			collisionBox.width = 40.0f;
			collisionBox.height = 35.0f;
			birdScoreCollisionBox = {collisionBox.x + collisionBox.width + 10,collisionBox.y ,0.1,100};
		}
		void bird::Render(){
			DrawTexturePro(bird_texture, (Rectangle){ 0.0f, 0.0f, (float)bird_texture.width, (float)bird_texture.height }, (Rectangle){ pos.x, pos.y, 50.0f, 40.0f }, (Vector2){ 0.0f, 0.0f }, 0.0f, RAYWHITE);
		}
		void bird::Unload(){
			UnloadTexture(bird_texture);
		}
		
		
bird::~bird(){
	Unload();
}
