#pragma once

#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"
#include "Constants.h"
#include "Scoreboard.h"
#include "Paddle.h"

#include <string>

static class Game {
public:

	//Spawning			/ Runs in Restart
	static void SpawnBall();
	static void SpawnBricks();
	static void SpawnPaddle(Paddle& paddle);

	//Drawing			/ Runs in Run
	static void DrawBall();
	static void DrawBricks();
	static void DrawPaddle(Paddle& paddle);

	//CollisionCheck	/ Runs in Run
	//checks ball collision for corners, paddle and bricks. triggers true if Ball hits bottom corner
	static bool BallCollision();
	static bool BallCollision(Paddle& paddle, Scoreboard& board);
	

	//Gameover Function handles scoring
	static void GameOver(Scoreboard& score);

	//handles input. specifically paddle input
	static void HandleInput(Paddle& paddle);
};



