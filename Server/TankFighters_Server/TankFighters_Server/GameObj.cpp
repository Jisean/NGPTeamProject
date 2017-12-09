#include "stdafx.h"
#include "GameObj.h"


GameObj::GameObj()
{
	ZeroMemory(&Packet, sizeof(PACKET));
	Packet.State = 1;
}


GameObj::~GameObj()
{
}

void GameObj::Move(int iX, int iY)
{
	Packet.fX += iX;
	Packet.fY += iY;
}