#pragma once

#include "protocol.h"

class CPlayer
{
public:
	CPlayer(int ID);
	~CPlayer();



public:
	KEY m_Key;
	INFO m_tInfo;
	int iHp;
	
};

