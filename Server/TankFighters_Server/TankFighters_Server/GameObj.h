#pragma once
#include "stdafx.h"


class GameObj
{
protected:
	OBJDATA objData;

public:
	GameObj();
	~GameObj();

	void Move(int posX, int posY);
	
	void SetData(OBJDATA data)
	{
		objData = data;
	}
	OBJDATA GetData(void)
	{
		return objData;
	}

};