#include "Player.h"


CPlayer::CPlayer(int ID)
{
	if (ID == 0)
	{
		m_tInfo.vPos.x = 500.f;
		m_tInfo.vPos.y = WINCY / 2.f;
		iHp = 40;
	}

	else
	{
		m_tInfo.vPos.x = 700.f;
		m_tInfo.vPos.y = WINCY / 2.f;
		iHp = 40;
	}
}


CPlayer::~CPlayer()
{
}


