#pragma once
#include "stdafx.h"


class GameObj
{
protected:
	PACKET Packet;

public:
	GameObj();
	~GameObj();

	void Move(int posX, int posY);
	
	void SetData(PACKET data)
	{
		Packet = data;
	}
	PACKET GetData(void)
	{
		return Packet;
	}

};