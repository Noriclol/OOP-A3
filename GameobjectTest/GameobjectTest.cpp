

#define PLAY_IMPLEMENTATION
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"
#include <iostream>

//void MainGameEntry(PLAY_IGNORE_COMMAND_LINE)
//{
//
//	Play::CreateManager(DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_SCALE);
//	Play::CentreAllSpriteOrigins();
//
//}
//
//// Called by PlayBuffer every frame (60 times a second!)
//bool MainGameUpdate(float elapsedTime)
//{
//
//	return Play::KeyDown(VK_ESCAPE);
//}
//
//// Gets called once when the player quits the game 
//int MainGameExit(void)
//{
//
//	Play::DestroyManager();
//	return PLAY_OK;
//}