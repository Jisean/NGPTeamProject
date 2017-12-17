#pragma once
#include "scene.h"

class CPlayer;
class CStage :
	public CScene
{
private:
	bool m_bIntrostart;
	bool m_bIntroend;
	bool m_bBgmRoof;

	DWORD dwBgmTime;
	KeyInput m_bKey;
	//KeyInput m_bKey2;
	CPlayer* m_pPlayer[2];


	DWORD m_dwProtocolTime = GetTickCount();


public:
	CStage(void);
	~CStage(void);

public:
	virtual HRESULT Initialize(void);
	virtual int Progress(CMainGame* pMain);
	virtual void Render(void);
	virtual void Release(void);
	void	KeyCheck(void);
	void    RecvSendData(CMainGame* pMain);

};
