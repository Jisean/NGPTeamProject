#pragma once
#include "stdafx.h"
#include "Timer.h"

class GameObj
{
protected:
	PACKET Packet;

public:
	GameObj();
	~GameObj();

	void Move(int iX, int iY,Timer timer);
	
	void SetData(PACKET data)
	{
		Packet = data;
	}
	PACKET GetData(void)
	{
		return Packet;
	}

};