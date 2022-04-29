#pragma once

//#define PLAY_USING_GAMEOBJECT_MANAGER
//#include "Play.h"
#include "Constants.h"

struct Paddle
{
	//dynamic position
	float PosX;
	float PosY;

	//Origin
	float oX = START_PADDLE_X;
	float oY = START_PADDLE_Y;

	float topRightX = 0.0f;
	float topRightY = 0.0f;
	float bottomLeftX = 0.0f;
	float bottomLeftY = 0.0f;

	Paddle(float posX, float posY);
	Paddle();
	void Reset();
};

