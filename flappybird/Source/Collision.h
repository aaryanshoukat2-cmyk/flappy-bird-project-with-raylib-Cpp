#pragma once
#include "raylib.h"
#include "GameTypes.h"
#include "bird.h"
struct CollisionCheck{
	void UpdatePipeCollision(Rectangle& player, Rectangle& Pipe,playerState& WLstate,GameState& state);
	void UpdateOutOfBounds(Vector2 pos,GameState& state, playerState& WLstate);
};
