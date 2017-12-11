#include "StdAfx.h"
#include "Stage.h"
#include "ObjFactory.h"
#include "Player.h"
#include "TileMgr.h"
#include "UI.h"
#include "SoundMgr.h"
#include "Enemy.h"

CStage::CStage(void)
{
	m_bIntrostart = false;
	m_bIntroend = false;
	m_bBgmRoof = false;

	dwBgmTime = GetTickCount();
}

CStage::~CStage(void)
{
	Release();
}

HRESULT CStage::Initialize(void)
{
	CObjMgr::GetInst()->AddObj(OBJ_UI,CObjFactory<CUI>::CreateObj());

	if (g_iPlayerNum == 0) // 1p일때
	{
		CObj* pObj = CObjFactory<CPlayer>::CreateObj(D3DXVECTOR3(200.f, WINCY / 2.f, 0.f));
		pObj->m_PlayerID = PLAYER_1P;
		CObjMgr::GetInst()->AddObj(OBJ_PLAYER, pObj);

		pObj = CObjFactory<CEnemy>::CreateObj(D3DXVECTOR3(700.f, WINCY / 2.f, 0.f));
		pObj->m_PlayerID = PLAYER_2P;
		CObjMgr::GetInst()->AddObj(OBJ_ENEMY, pObj);
	}
	else if(g_iPlayerNum == 1) //2p일때
	{
		CObj* pObj = CObjFactory<CPlayer>::CreateObj(D3DXVECTOR3(700.f, WINCY / 2.f, 0.f));
		pObj->m_PlayerID = PLAYER_2P;
		CObjMgr::GetInst()->AddObj(OBJ_ENEMY, pObj);

		pObj = CObjFactory<CEnemy>::CreateObj(D3DXVECTOR3(200.f, WINCY / 2.f, 0.f));
		pObj->m_PlayerID = PLAYER_1P;
		CObjMgr::GetInst()->AddObj(OBJ_PLAYER, pObj);
	}

	g_bGameStarted = true;
	return S_OK;
}

int CStage::Progress(void)
{	
	CObjMgr::GetInst()->Progress();

	CTileMgr::GetInst()->Progress();

	if(*(CObjMgr::GetInst()->GetObjList()[OBJ_PLAYER].front()->GetRoomType()) !=12 && *(CObjMgr::GetInst()->GetObjList()[OBJ_PLAYER].front()->GetRoomType()) !=5)
	{

		if(m_bIntrostart == false)
		{
			dwBgmTime = GetTickCount();
			CSoundMgr::GetInst()->PlayBgm(L"basementintro.ogg");
			m_bIntrostart = true;
		}
		if(dwBgmTime + 13700 < GetTickCount() && m_bIntroend == false)
		{
			m_bIntroend = true;
			CSoundMgr::GetInst()->PlayBgm(L"basement.ogg");
			dwBgmTime = GetTickCount();
		}

		if(dwBgmTime + 116500 < GetTickCount() && m_bBgmRoof == false)
		{
			m_bBgmRoof = true;
			CSoundMgr::GetInst()->PlayBgm(L"basement.ogg");
			dwBgmTime = GetTickCount();
		}

		if(dwBgmTime + 116500 < GetTickCount() && m_bBgmRoof == true)
		{
			m_bBgmRoof = false;
			CSoundMgr::GetInst()->PlayBgm(L"basement.ogg");
			dwBgmTime = GetTickCount();
		}
	}
	return 0;
}

void CStage::Render(void)
{
	CObjMgr::GetInst()->Render();
}

void CStage::Release(void)
{

}
