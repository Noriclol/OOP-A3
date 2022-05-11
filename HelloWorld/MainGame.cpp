#include "game.h"
#include "Constants.h"


#include <algorithm>

using namespace std;

Paddle paddle;
Scoreboard scoreboard;

GameState state = State_Restart;

void DrawScoreboard() {
	int Xoffset = 100, Yoffset = 80, rowSpace = 30;
	int ScoresShown = 5;
	Play::DrawDebugText(Point2D((DISPLAY_WIDTH / 2) - Xoffset, (DISPLAY_HEIGHT / 2) + Yoffset), "HighScores");

	for (int i = 0; i <= ScoresShown; i++)
	{
		string line = to_string(0);;
		if (i < scoreboard.board.filelength)
		{
			line = to_string(scoreboard.board.scores[i]);
		}
		Play::DrawDebugText(Point2D((DISPLAY_WIDTH / 2) - Xoffset, (DISPLAY_HEIGHT / 2) + Yoffset + (rowSpace * (i + 1)) ), line.c_str());
	}
}

void DrawDebugBoard() {

	//string top = "top: " + to_string(scoreboard.board.top);

	//string str0 = "n0:" + to_string(scoreboard.board.stack[0]);
	//string str1 = "n1:" + to_string(scoreboard.board.stack[1]);
	//string str2 = "n2:" + to_string(scoreboard.board.stack[2]);
	//string str3 = "n3:" + to_string(scoreboard.board.stack[3]);
	//string str4 = "n4:" + to_string(scoreboard.board.stack[4]);

	//Play::DrawDebugText(Point2D((DISPLAY_WIDTH / 2) - 100, h + 80 + (DISPLAY_HEIGHT / 2)), "DebugBoard:");

	//Play::DrawDebugText(Point2D((DISPLAY_WIDTH / 2) - 100, h + 100 + (DISPLAY_HEIGHT / 2)), top.c_str());

	//Play::DrawDebugText(Point2D((DISPLAY_WIDTH / 2) - 100, h + 120 + (DISPLAY_HEIGHT / 2)), str0.c_str());
	//Play::DrawDebugText(Point2D((DISPLAY_WIDTH / 2) - 100, h + 140 + (DISPLAY_HEIGHT / 2)), str1.c_str());
	//Play::DrawDebugText(Point2D((DISPLAY_WIDTH / 2) - 100, h + 160 + (DISPLAY_HEIGHT / 2)), str2.c_str());
	//Play::DrawDebugText(Point2D((DISPLAY_WIDTH / 2) - 100, h + 180 + (DISPLAY_HEIGHT / 2)), str3.c_str());
	//Play::DrawDebugText(Point2D((DISPLAY_WIDTH / 2) - 100, h + 200 + (DISPLAY_HEIGHT / 2)), str4.c_str());

}

void DrawCurrentScore() {
	string str = to_string(scoreboard.currentScore);

	Play::DrawDebugText(Point2D(100 + (DISPLAY_WIDTH / 2), 230 + (DISPLAY_HEIGHT / 2)), "Score:");
	Play::DrawDebugText(Point2D(130 + (DISPLAY_WIDTH / 2), 230 + (DISPLAY_HEIGHT / 2)), str.c_str());
}

// The entry point for a PlayBuffer program
void MainGameEntry( PLAY_IGNORE_COMMAND_LINE )
{
	
	Play::CreateManager( DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_SCALE );
	Play::CentreAllSpriteOrigins();
	//scoreboard = Scoreboard();
	state = State_Restart;
}

// Called by PlayBuffer every frame (60 times a second!)
bool MainGameUpdate( float elapsedTime )
{
	//Clear Buffer
	//Play::ClearDrawingBuffer(Play::cBlack);

	int i = state;

	//Init Object References
	std::vector<int> ballIds = Play::CollectGameObjectIDsByType(Type_Ball);
	std::vector<int> brickIds = Play::CollectGameObjectIDsByType(Type_Brick);


	//CURRENT CONFIG:: Only ball spawn / update
	//Runs main Game Loop and Reset Loop
	switch (i)
	{


	case State_Run:
		Play::ClearDrawingBuffer(Play::cBlack);
		//Check Collisions
		if (Game::BallCollision(paddle, scoreboard)) //this will automatically trigger once ball has triggered once!! 
		{
			Game::GameOver(scoreboard);
			state = State_Restart;
			break;
		}

		//Handle Input
		Game::HandleInput(paddle);

		//drawCall
		Game::DrawBall();
		Game::DrawBricks();
		Game::DrawPaddle(paddle);

		//DrawScoreboard();
		DrawCurrentScore();
		DrawScoreboard();

		
		break;


	case State_Restart:
		Play::ClearDrawingBuffer(Play::cBlue);

		Play::DestroyGameObjectsByType(Type_Brick);
		Play::DestroyGameObjectsByType(Type_Ball);

		Game::SpawnBall();
		Game::SpawnBricks();
		Game::SpawnPaddle(paddle);

		state = State_Run;
		break;
	}

	Play::PresentDrawingBuffer();
	return Play::KeyDown( VK_ESCAPE );
}

// Gets called once when the player quits the game 
int MainGameExit( void )
{
	
	Play::DestroyManager();
	return PLAY_OK;
}