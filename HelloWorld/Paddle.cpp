//#define PLAY_IMPLEMENTATION
//#define PLAY_USING_GAMEOBJECT_MANAGER
//#include "Play.h"
#include "Paddle.h"

Paddle::Paddle(float posX, float posY)
{
	this->PosX = posX;
	this->PosY = posY;
}
Paddle::Paddle() {
	this->PosX =  1000.0f;
	this->PosY =  1000.0f;
}
//void Paddle::Reset() 
//{
//	this->PosX = oX;
//	this->PosY = oX;
//}



