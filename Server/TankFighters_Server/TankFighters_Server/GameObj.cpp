#include "stdafx.h"
#include "GameObj.h"


GameObj::GameObj()
{
}


GameObj::~GameObj()
{
}

void GameObj::Move(int posX, int posY)
{
	objData.posX += posX;
	objData.posY += posY;
}