#pragma once
#include "raylib.h"
#include "Pipe.h"
#include "iostream"
#include "GameTypes.h"

struct CollisionCheck;
struct bird;

class Game{
	private:
		int score;
	public:
	Font flappyFont; 
	bool IsPaused;


	GameState state;
	Rectangle button;
	playerState WLstate;
	void ScoreIncrease();
	void ScoreUpdate(PipeSet& pipe,bird& player);
	void PauseCheck();
	void PauseScreen();
	void RestartScreen(PipeFunctions& pipeF,bird& player);
	void WinScreen();
	int GetScore();
	void ScoreDisplayer();
	void StartScreen();
	void ButtonListener(bird& player);
	void InputStateManager(bird& player,PipeFunctions& pipeF);
	void UpdateStateManager(bird& player,PipeFunctions& pipeF,CollisionCheck& check);
	void RenderStateManager(bird& player,PipeFunctions& pipeF);
	Game();
	~Game();
};
