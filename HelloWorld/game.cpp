#define PLAY_IMPLEMENTATION
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"
#include "game.h"
#include <iostream>
#include <cstdlib>
#include <ctime>


//Spawning functions

void Game::SpawnBall()
{
	const int objectId = Play::CreateGameObject(ObjectType::Type_Ball, {START_BALL_X, START_BALL_Y }, 4, "ball");
	GameObject& ball = Play::GetGameObject(objectId);
	ball.velocity = normalize({ -1, -1 }) * BALL_SPEED;
}

void Game::SpawnBricks()
{
	for (int y = 0; y < BRICK_AMOUNT_Y; y++)
	{
		for (int x = 0; x < BRICK_AMOUNT_X; x++)
		{
			Play::CreateGameObject(ObjectType::Type_Brick, { BRICK_OFFSET_X + x * BRICK_SPACING_X, BRICK_OFFSET_Y + y * BRICK_SPACING_Y }, 6, "brick");
		}
	}
}

void Game::SpawnPaddle(Paddle& paddle)
{
	paddle = Paddle(START_PADDLE_X, START_PADDLE_Y);
}

//DrawCall Functions

void Game::DrawBall()
{
	std::vector<int> ballIds = Play::CollectGameObjectIDsByType(Type_Ball);

	for (int i = 0; i < ballIds.size(); i++)
	{
		GameObject& ball = Play::GetGameObject(ballIds[i]);
		Play::UpdateGameObject(ball);
		Play::DrawObject(ball);
	}
}

void Game::DrawBricks()
{
	std::vector<int> brickIds = Play::CollectGameObjectIDsByType(Type_Brick);
	for (int i = 0; i < brickIds.size(); i++)
	{
		Play::UpdateGameObject(Play::GetGameObject(brickIds[i]));
		Play::DrawObject(Play::GetGameObject(brickIds[i]));
	}
}

void Game::DrawPaddle(Paddle& paddle)
{
	paddle.topRightX = paddle.PosX + PADDLE_WIDTH / 2;
	paddle.topRightY = paddle.PosY + PADDLE_HEIGHT / 2;

	paddle.bottomLeftX = paddle.PosX - PADDLE_WIDTH / 2;
	paddle.bottomLeftY = paddle.PosY - PADDLE_HEIGHT / 2;

	Play::DrawRect(Point2D(paddle.bottomLeftX, paddle.bottomLeftY), Point2D(paddle.topRightX, paddle.topRightY), Play::cBlue, true);
}

//Collisionhandling

bool Game::BallCollision() {
	std::vector<int> ballIds = Play::CollectGameObjectIDsByType(Type_Ball);
	for (int i = 0; i < ballIds.size(); i++)
	{
		GameObject& ball = Play::GetGameObject(ballIds[i]);

		float velocityX = ball.velocity.x;
		float velocityY = ball.velocity.y;
		float positionX = ball.pos.x;
		float positionY = ball.pos.y;



		//Collision w Walls
		if (positionX < 0)
		{
			Play::GetGameObject(ballIds[i]).velocity.x = BALL_SPEED;
			/*ball.pos.x = START_BALL_X;
			ball.pos.y = START_BALL_Y;*/
			//return true;

		}
		if (positionY < 0)
		{
			Play::GetGameObject(ballIds[i]).velocity.y = BALL_SPEED;
			/*ball.pos.x = START_BALL_X;
			ball.pos.y = START_BALL_Y;*/
			//return true;
		}
		if (positionX > DISPLAY_WIDTH)
		{
			Play::GetGameObject(ballIds[i]).velocity.x = -BALL_SPEED;
			//ball.pos.x = START_BALL_X;
			//ball.pos.y = START_BALL_Y;
			//return true;

		}
		if (positionY > DISPLAY_HEIGHT)
		{
			//if any ball is out of bounds
			//Play::GetGameObject(ballIds[i]).velocity.y = -BALL_SPEED;
			ball.pos.x = START_BALL_X;
			ball.pos.y = START_BALL_Y;

			srand((unsigned int)time(NULL));
			float a = 5.0;

			
			ball.velocity = normalize({ (float(rand()) / float((RAND_MAX)) * a), -1 }) * BALL_SPEED;
			Play::DestroyGameObject(ballIds[i]);
			//Play::DestroyGameObjectsByType(Type_Ball);
			return true;
		}
	}
	//all is well and game keeps running
	return false;

}

bool Game::BallCollision(Paddle& paddle, Scoreboard& board)
{
	std::vector<int> ballIds = Play::CollectGameObjectIDsByType(Type_Ball);
	std::vector<int> brickIds = Play::CollectGameObjectIDsByType(Type_Brick);


	//for all balls in scene
	for (int i = 0; i < ballIds.size(); i++)
	{
		GameObject& ball = Play::GetGameObject(ballIds[i]);

		float velocityX = ball.velocity.x;
		float velocityY = ball.velocity.y;
		float positionX = ball.pos.x;
		float positionY = ball.pos.y;



		//Collision w Walls
		if (positionX < 0)
		{
			Play::GetGameObject(ballIds[i]).velocity.x = BALL_SPEED;

		}
		if (positionY < 0)
		{
			Play::GetGameObject(ballIds[i]).velocity.y = BALL_SPEED;
		}
		if (positionX > DISPLAY_WIDTH)
		{
			Play::GetGameObject(ballIds[i]).velocity.x = -BALL_SPEED;

		}
		if (positionY > DISPLAY_HEIGHT)
		{
			//if any ball is out of bounds
			Play::DestroyGameObject(ballIds[i]);
			return true;
		}


		//Collision w Bricks
		for (int j = 0; j < brickIds.size(); j++)
		{
			GameObject& ball = Play::GetGameObject(ballIds[i]);
			GameObject& brick = Play::GetGameObject(brickIds[j]);

			if (Play::IsColliding(ball, brick)) {
				Play::DestroyGameObject(brickIds[j]);

				board.Score(1);

				ball.velocity.x = (ball.velocity.x < 0) ? BALL_SPEED : -BALL_SPEED;
				ball.velocity.y = (ball.velocity.y < 0) ? BALL_SPEED : -BALL_SPEED;

			}
		}

		//Collision with paddle
		const float dx = ball.pos.x - max(paddle.bottomLeftX, std::min(ball.pos.x, paddle.topRightX));
		const float dy = ball.pos.y - max(paddle.bottomLeftY, min(ball.pos.y, paddle.topRightY));
		bool collided = (dx * dx + dy * dy) < (ball.radius * ball.radius);

		if (collided)
		{
			Play::GetGameObject(ballIds[i]).velocity.y = (Play::GetGameObject(ballIds[i]).velocity.y < 0) ? BALL_SPEED : -BALL_SPEED;;
		}
	}
	//all is well and game keeps running
	return false;
}

//Score count on Gameover

void Game::GameOver(Scoreboard& score) {


	//is score new
	unsigned int newscore = score.currentScore;
	score.currentScore = 0;
	bool isNew = true;
	for (unsigned int i = 0; i < sizeof(score.board.n); i++)
	{
		if (score.board.stack[i] == newscore)
		{
			isNew = false;
		}
	}

	if (newscore == 0)
	{
		isNew = false;
	}


	if (isNew)
	{
		//push new score
		score.board.Push(newscore);

		//sort Scoreboard
		Stack input = score.board;
		Stack tmpStack = score.SortScoreboard(input);
		score.board = tmpStack;

	}
}

//handle Input

void Game::HandleInput(Paddle& paddle)
{
	if (Play::KeyDown(VK_LEFT)) {


		if (paddle.bottomLeftX > 0)
		{
			//Play::DrawDebugText(Point2D(DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2), "PaddleLeft!");
			paddle.PosX -= PADDLE_SPEED;
		}

		else {
			//Play::DrawDebugText(Point2D(DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2), "Corner!");
		}
	}
	if (Play::KeyDown(VK_RIGHT)) {


		if (paddle.topRightX < DISPLAY_WIDTH) {
			//Play::DrawDebugText(Point2D(DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2), "PaddleRight!");
			paddle.PosX += PADDLE_SPEED;
		}

		else {
			//Play::DrawDebugText(Point2D(DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2), "Corner!");
		}

	}
}

//bool Game::StepFrame(float timeSinceStart, Scoreboard& score)
//{
//	//Collect gameobjects
//	std::vector<int> ballIds = Play::CollectGameObjectIDsByType(Type_Ball);
//	std::vector<int> brickIds = Play::CollectGameObjectIDsByType(Type_Brick);
//
//	//Draw/Update Ball
//	for (int i = 0; i < ballIds.size(); i++)
//	{
//		GameObject& ball = Play::GetGameObject(ballIds[i]);
//
//		float velocityX = ball.velocity.x;
//		float velocityY = ball.velocity.y;
//		float positionX = ball.pos.x;
//		float positionY = ball.pos.y;
//
//		if (positionX < 0)
//		{
//			Play::GetGameObject(ballIds[i]).velocity.x = BALL_SPEED;
//
//		}
//		if (positionY < 0)
//		{
//			Play::GetGameObject(ballIds[i]).velocity.y = BALL_SPEED;
//		}
//
//		if (positionX > DISPLAY_WIDTH)
//		{
//			Play::GetGameObject(ballIds[i]).velocity.x = -BALL_SPEED;
//
//		}
//		if (positionY > DISPLAY_HEIGHT)
//		{
//			//Game over
//			Game::GameOver(score);
//			//Reset Scene
//			return true;
//		}
//
//		//If Border Hit
//		//ball.velocity.x = (ball.velocity.x < 0) ? BALL_SPEED : -BALL_SPEED;
//		//ball.velocity.y = (ball.velocity.y < 0) ? BALL_SPEED : -BALL_SPEED;
//
//		Play::UpdateGameObject(Play::GetGameObject(ballIds[i]));
//		Play::DrawObject(Play::GetGameObject(ballIds[i]));
//	}
//
//	//Check for collisions between ball and bricks
//	for (int i = 0; i < ballIds.size(); i++) {
//		for (int j = 0; j < brickIds.size(); j++)
//		{
//			GameObject& ball = Play::GetGameObject(ballIds[i]);
//			GameObject& brick = Play::GetGameObject(brickIds[j]);
//
//			if (Play::IsColliding(ball, brick)) {
//				Play::DestroyGameObject(brickIds[j]);
//
//				score.Score(1);
//
//				ball.velocity.x = (ball.velocity.x < 0) ? BALL_SPEED : -BALL_SPEED;
//				ball.velocity.y = (ball.velocity.y < 0) ? BALL_SPEED : -BALL_SPEED;
//				
//			}
//		}
//
//	}
//
//
//	//Render Bricks
//	for (int i = 0; i < brickIds.size(); i++)
//	{
//
//
//
//		Play::UpdateGameObject(Play::GetGameObject(brickIds[i]));
//		Play::DrawObject(Play::GetGameObject(brickIds[i]));
//	}
//
//
//	return false;
//}





