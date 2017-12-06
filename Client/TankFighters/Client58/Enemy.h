#pragma once
#include "obj.h"

class CEnemy :
	public CObj
{
protected:
	bool			m_bHasBodynHead;
	bool			m_bBlinking;
	D3DXVECTOR3		m_vecOffset;
	map<wstring, UNITDATA*> m_mapStat;

public:
	CEnemy(void);
	~CEnemy(void);

public:
	void WorldMatrix(void);

public:
	virtual HRESULT Initialize(void);
	virtual int Progress(void);
	virtual void Render(void);
	virtual void Release(void);

};
