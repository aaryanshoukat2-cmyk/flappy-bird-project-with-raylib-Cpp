#pragma once
#include "Pipe.h"
#include "raylib.h"
#include "Game.h"
enum class birdState{
	alive,
	dead,
	none,
};
struct bird{
	//bird properties
	Vector2 pos;
	Texture2D bird_texture;
	float gravity;
	float velocityY;
	Rectangle collisionBox;
	birdState state;
	Rectangle birdScoreCollisionBox;
	//functions
	void Create();
	void Jump();
	void ScoreUpdate(PipeSet& pipe,Game& game);
	void Input();
	void Update();
	void Render();
	void Unload();
	bird();
	~bird();

};

