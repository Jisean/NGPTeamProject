#pragma once
#include "scene.h"

class CLogo :
	public CScene
{
private:
	HANDLE				m_hThread;
	CRITICAL_SECTION	m_Crt;
	RECT				rcLDBar;
	bool				m_bLoading;
	bool				m_bLoadingThreadClose;

public:
	CLogo(void);
	~CLogo(void);

public:
	static unsigned int __stdcall LoadThread(void* pArg);
	CRITICAL_SECTION	GetCrt(void);
	void	SetLoading(bool bTF);

public:
	virtual HRESULT Initialize(void);
	virtual int Progress(void);
	virtual void Render(void);
	virtual void Release(void);

};
