#include "Bullet.h"



CBullet::CBullet()
{
}


CBullet::~CBullet()
{
}

int CBullet::Update(int Count /*= 0*/)
{
	if (iHp == 0)
	{
		return iHp;
	}

#ifdef _DEBUG
	m_tInfo.vPos += m_tInfo.vDir * 0.2f;
#endif // !_DEBUG

#ifndef _DEBUG
	m_tInfo.vPos += m_tInfo.vDir * 0.005f;
#endif // !_DEBUG

	
	

	if (m_tInfo.vPos.x > WINCX)
	{
		iHp = 0;
		return iHp;
	}

	if (m_tInfo.vPos.x < 0)
	{
		iHp = 0;
		return iHp;
	}

	if (m_tInfo.vPos.y > WINCY)
	{
		iHp = 0;
		return iHp;
	}

	if (m_tInfo.vPos.y < 0)
	{
		iHp = 0;
		return iHp;
	}

	return iHp;
}

CBullet* CBullet::Create(float fX, float fY, KEY Key, OBJ_ID _ID)
{
	CBullet* pBullet = new CBullet;
	pBullet->m_tInfo.vPos.x = fX;
	pBullet->m_tInfo.vPos.y = fY;
	pBullet->ID = _ID;

	if (Key.bDShoot)
		pBullet->m_tInfo.vDir = D3DXVECTOR3(0.f, 1.f, 0.f);

	if (Key.bUShoot)
		pBullet->m_tInfo.vDir = D3DXVECTOR3(0.f, -1.f, 0.f);

	if (Key.bLShoot)
		pBullet->m_tInfo.vDir = D3DXVECTOR3(-1.f, 0.f, 0.f);

	if (Key.bRShoot)
		pBullet->m_tInfo.vDir = D3DXVECTOR3(1.f, 0.f, 0.f);

	return pBullet;
}
