#pragma once

#include "stdafx.h"
#include "define.h"

typedef struct tagTile
{
	D3DXVECTOR3		vPos;
	D3DXVECTOR3		vSize;
	BYTE			byOption;
	BYTE			byDrawID;

}TILE;

class CObj;
class CTileMgr
{
DECLARE_SINGLETON(CTileMgr)

private:
	list<CObj*>* pObjList;
	float		pfx;
	float		pfy;
	float		ptearfx;
	float		ptearfy;
	float		pmonsterfx;
	float		pmonsterfy;
	float		pbulletfx;
	float		pbulletfy;
	float		pexplosionfx;
	float		pexplosionfy;
	bool		b_DoorSound1;
	bool		b_DoorSound2;
	bool		b_DoorSound3;
	bool		b_DoorSound4;
	bool		b_DoorSound5;


	bool		m_bTile = false; 
	vector<TILE*> m_vecNonMoveTile;
public:
	void Progress(void);
	void PlayerTile(void);
	void TearTile(void);
	void MonsterTile(void);
	void BulletTile(void);
	void DoorTile(void);
	void BombTile(void);
private:
	CTileMgr(void);
	~CTileMgr(void);
};
