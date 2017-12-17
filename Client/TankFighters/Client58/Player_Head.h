#pragma once
#include "player.h"

class CPlayer_Head :
	public CPlayer
{
private:
	DWORD m_dwState2;
	FRAME m_tStartFrame;
	list<CObj*>* pObjList;
	float	m_fFramespeed;
	bool	m_bTearFired;

public:
	CPlayer* m_pPlayer = nullptr;

public:
	void FrameMove(void);
	void StateKeyInput(KEY KeyValue);
public:
	CPlayer_Head(void);
	~CPlayer_Head(void);

public:
	virtual HRESULT Initialize(void);
	virtual int Progress(void);
	virtual void Render(void);
	virtual void Release(void);
};
