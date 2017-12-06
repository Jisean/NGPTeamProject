#pragma once
#include "Enemy.h"

class CEnemy_Head :
	public CEnemy
{
private:
	DWORD m_dwState2;
	FRAME m_tStartFrame;
	list<CObj*>* pObjList;
	float	m_fFramespeed;
	bool	m_bTearFired;

public:
	CEnemy* m_pEnemy = nullptr;

public:
	void FrameMove(void);
	void StateKeyInput(void);
public:
	CEnemy_Head(void);
	~CEnemy_Head(void);

public:
	virtual HRESULT Initialize(void);
	virtual int Progress(void);
	virtual void Render(void);
	virtual void Release(void);
};
