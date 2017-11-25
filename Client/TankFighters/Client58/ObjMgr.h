#pragma once

#include "Include.h"

class CObj;
class CObjMgr
{
DECLARE_SINGLETON(CObjMgr)

private:
	list<CObj*>		m_ObjList[OBJ_END];
	vector<CObj*>	m_vecRender[R_END];
	float pfx;
	float pfy;

public:

	static bool Compare(CObj* pDest, CObj* pSource);
	void AddObj(OBJID _eID, CObj* pObj);

	const vector<TILE*>* GetTile(void);

	HRESULT Initialize(void);
	void Progress(void);
	void Render(void);
	void Release(void);
	list<CObj*>*	GetObjList(void)
	{
		return m_ObjList;
	}


	void TearCheck(void);
	void BulletCheck(void);


	void Battle(void); // KSH
	
private:
	CObjMgr(void);
	~CObjMgr(void);
};
