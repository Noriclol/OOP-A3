#pragma once

//Display
const int DISPLAY_WIDTH = 320;
const int DISPLAY_HEIGHT = 480;
const int DISPLAY_SCALE = 1;
const int DISPLAY_WIDTH_CENTER = DISPLAY_WIDTH / 2;
const int DISPLAY_HEIGHT_CENTER = DISPLAY_HEIGHT / 2;


//Paddle
const int START_PADDLE_X = DISPLAY_WIDTH / 2;
const int START_PADDLE_Y = DISPLAY_HEIGHT - 50;
const int PADDLE_WIDTH = 40;
const int PADDLE_HEIGHT = 5;
const float PADDLE_SPEED = 3.5f;

//Ball
const int START_BALL_X = DISPLAY_WIDTH / 2;
const int START_BALL_Y = DISPLAY_HEIGHT - 60;
const float BALL_SPEED = 6.0f;

//Bricks
const int BRICK_AMOUNT_X = 18;
const int BRICK_AMOUNT_Y = 4;
const int BRICK_OFFSET_X = 17;
const int BRICK_OFFSET_Y = 11;
const int BRICK_SPACING_X = 17;
const int BRICK_SPACING_Y = 11;

const float h = 30.0f;





enum ObjectType {
	Type_Ball,
	Type_Player,
	Type_Brick,
	Type_GameBoard
};

enum GameState {
	State_Run,
	State_Restart
};


