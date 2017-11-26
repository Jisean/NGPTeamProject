#pragma once
#include "scene.h"

class CStage :
	public CScene
{
private:
	bool m_bIntrostart;
	bool m_bIntroend;
	bool m_bBgmRoof;

	DWORD dwBgmTime;

public:
	CStage(void);
	~CStage(void);

public:
	virtual HRESULT Initialize(void);
	virtual int Progress(void);
	virtual void Render(void);
	virtual void Release(void);

};
