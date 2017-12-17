#pragma once

#include "Include.h"

class	CScene;
class CMainGame;
class CSceneMgr
{
	DECLARE_SINGLETON(CSceneMgr)
private:
	CScene*		m_pScene;

public:
	CMainGame* m_pMain = nullptr;
	OBJ_ID     m_ID = ID_END;


	void SetID(OBJ_ID ID)
	{
		cout << ID << endl;
		m_ID = ID;
	}
public:
	void		SetScene(SCENEID _eScene);
	void		Progress(CMainGame* pMain);
	void		Render(void);
	void		Release(void);

private:
	CSceneMgr(void);
	~CSceneMgr(void);
};
