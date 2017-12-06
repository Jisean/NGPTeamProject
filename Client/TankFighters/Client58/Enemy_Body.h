#pragma once
#include "Enemy.h"

class CEnemy_Body :
	public CEnemy
{
private:
	list<CObj*>* pObjList;

public:
	CEnemy* m_pEnemy = nullptr;

public:
	void FrameMove(void);
	void StateKeyInput(void);
public:
	CEnemy_Body(void);
	~CEnemy_Body(void);
public:
	virtual HRESULT Initialize(void);
	virtual int Progress(void);
	virtual void Render(void);
	virtual void Release(void);
};
