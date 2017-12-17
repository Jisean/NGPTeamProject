#pragma once

#include "protocol.h"


class CBullet
{
public:
	CBullet();
	~CBullet();


public:
	KEY m_Key;
	INFO m_tInfo;
	Key KeyCheck;
	OBJ_ID ID = ID_END;
	int iHp = 1;
	bool bDeath = false;

public:
	int Update(int Count = 0);
	static CBullet* Create(float fX, float fY, KEY Key, OBJ_ID _ID);
};

