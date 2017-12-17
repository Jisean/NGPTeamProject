#include "StdAfx.h"
#include "Stage.h"
#include "ObjFactory.h"
#include "Player.h"
#include "TileMgr.h"
#include "UI.h"
#include "SoundMgr.h"
#include "ObjMgr.h"
#include "MainGame.h"
#include "Player_Body.h"
#include "Player_Head.h"
#include "SceneMgr.h"
#include "Tear.h"

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
	cout << "스테이지 시작 " << endl;
	CObjMgr::GetInst()->AddObj(OBJ_UI,CObjFactory<CUI>::CreateObj());

	
	CObj* pObj = CObjFactory<CPlayer>::CreateObj(D3DXVECTOR3(500.f, WINCY / 2.f, 0.f));
	pObj->m_PlayerID = PLAYER_1P;
	CObjMgr::GetInst()->AddObj(OBJ_PLAYER, pObj);

	m_pPlayer[0] = dynamic_cast<CPlayer*>(pObj);

	pObj = CObjFactory<CPlayer>::CreateObj(D3DXVECTOR3(700.f, WINCY / 2.f, 0.f));
	pObj->m_PlayerID = PLAYER_2P;
	CObjMgr::GetInst()->AddObj(OBJ_PLAYER, pObj);
	m_pPlayer[1] = dynamic_cast<CPlayer*>(pObj);


	g_bGameStarted = true;
	return S_OK;
}

int CStage::Progress(CMainGame* pMain)
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

	/////////////////////////////////////////////////////////////////////////////////////////////
	//통신

	ZeroMemory(&m_bKey, sizeof(m_bKey));

	KeyCheck();
	RecvSendData(pMain);


	return 0;
}

void CStage::Render(void)
{
	CObjMgr::GetInst()->Render();
}

void CStage::Release(void)
{

}

void CStage::KeyCheck(void)
{

	if (GetAsyncKeyState(VK_RIGHT))
		m_bKey.bRShoot = true;

	if (GetAsyncKeyState(VK_LEFT))
		m_bKey.bLShoot = true;

	if (GetAsyncKeyState(VK_UP))
		m_bKey.bUShoot = true;

	if (GetAsyncKeyState(VK_DOWN))
		m_bKey.bDShoot = true;

	if (GetAsyncKeyState('D'))
		m_bKey.bRight = true;

	if (GetAsyncKeyState('A'))
		m_bKey.bLeft = true;

	if (GetAsyncKeyState('W'))
		m_bKey.bUp = true;

	if (GetAsyncKeyState('S'))
		m_bKey.bDown = true;
}

void CStage::RecvSendData(CMainGame* pMain)
{
	int otherPlayer = 0;

	if (CSceneMgr::GetInst()->m_ID == ID_PLAYER)
		otherPlayer = 1;

	else
		otherPlayer = 0;


	if (m_dwProtocolTime + 15< GetTickCount())
	{

		m_dwProtocolTime = GetTickCount();


		int retval = send(pMain->sock, (char *)&m_bKey, sizeof(KEY), 0);
		if (retval == SOCKET_ERROR)
		{
			err_display("send()");
			return;
		}

		ORIGINPACKET Origin;
		ZeroMemory(&Origin, sizeof(ORIGINPACKET));
		retval = recvn(pMain->sock, (char*)&Origin, sizeof(ORIGINPACKET), 0);;

		if (retval == SOCKET_ERROR)
		{
			err_display("recv()");
			return;
		}

		m_pPlayer[CSceneMgr::GetInst()->m_ID]->m_tInfo.vPos.x = Origin.PlayerInfo1.fX;
		m_pPlayer[CSceneMgr::GetInst()->m_ID]->m_tInfo.vPos.y = Origin.PlayerInfo1.fY;
		m_pPlayer[CSceneMgr::GetInst()->m_ID]->PlayerBody->StateKeyInput(m_bKey);
		m_pPlayer[CSceneMgr::GetInst()->m_ID]->PlayerHead->StateKeyInput(m_bKey);
		m_pPlayer[CSceneMgr::GetInst()->m_ID]->fHp = (float)Origin.PlayerInfo1.Hp;



		m_pPlayer[otherPlayer]->m_tInfo.vPos.x = Origin.PlayerInfo2.fX;
		m_pPlayer[otherPlayer]->m_tInfo.vPos.y = Origin.PlayerInfo2.fY;
		m_pPlayer[otherPlayer]->PlayerBody->StateKeyInput(Origin.KeyValue);
		m_pPlayer[otherPlayer]->PlayerHead->StateKeyInput(Origin.KeyValue);

		UINT CurrentSize = CObjMgr::GetInst()->GetObjList()[OBJ_TEAR].size();
		UINT PacketSize = Origin.BulletSize;
		int addtear = PacketSize - CurrentSize;
		if (addtear > 0)
		{
			for (int i = 0; i < addtear; ++i)
			{
				CObj* pObj = nullptr;
				pObj = CTear::Create(&Origin.BulletInfo[PacketSize - addtear + i]);
				CObjMgr::GetInst()->GetObjList()[OBJ_TEAR].push_back(pObj);
			}
		}

		int INDEX = 0;

		auto iter = CObjMgr::GetInst()->GetObjList()[OBJ_TEAR].begin();
		auto iter_end = CObjMgr::GetInst()->GetObjList()[OBJ_TEAR].end();

		for (iter; iter != iter_end; ++iter)
		{
			dynamic_cast<CTear*>(*iter)->SetPacket(&Origin.BulletInfo[INDEX]);
			++INDEX;
		}

	}
}
