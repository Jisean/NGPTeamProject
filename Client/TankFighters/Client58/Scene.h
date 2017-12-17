#pragma once

#include "Include.h"
#include "ObjMgr.h"

class CMainGame;
class CScene
{
protected:
	CObjMgr*		m_pObjMgr;

public:
	virtual HRESULT	Initialize(void)PURE;
	virtual int		Progress(CMainGame* pMain)PURE;
	virtual void	Render(void)PURE;
	virtual void	Release(void)PURE;

public:
	CScene(void);
	virtual ~CScene(void);
};
