#include "StdAfx.h"
#include "Enemy_Head.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "KeyMgr_Song.h"
#include "ObjFactory.h"
#include "Enemy_Body.h"
#include "Tear.h"
#include "SoundMgr.h"
CEnemy_Head::CEnemy_Head(void)
{
	pObjList = CObjMgr::GetInst()->GetObjList();
}

CEnemy_Head::~CEnemy_Head(void)
{
	Release();
}

HRESULT CEnemy_Head::Initialize(void)
{
	m_wstrObjKey = L"Enemy";
	m_wstrStateKey = L"Head";
	m_tFrame = FRAME(0.f, 1.f, 1.f);
	m_dwState = HEAD_DOWN;
	m_dwState2 = BODY_DOWN;
	m_dwPrevState = HEAD_DOWN;
	m_tStartFrame = m_tFrame;
	m_fFramespeed = 2.f;
	m_bTearFired = false;
	m_RenderType = R_WORLDOBJ_HEAD;
	return S_OK;
}

int CEnemy_Head::Progress(void)
{
	FrameMove();
	if (m_dwState == HEAD_DOWN)
	{
		m_tInfo.vPos.x = m_pEnemy->GetInfo()->vPos.x;
		m_tInfo.vPos.y = m_pEnemy->GetInfo()->vPos.y + 15.f;
	}
	else if (m_dwState == HEAD_UP)
	{
		m_tInfo.vPos.x = m_pEnemy->GetInfo()->vPos.x;
		m_tInfo.vPos.y = m_pEnemy->GetInfo()->vPos.y - 15.f;
	}
	else if (m_dwState == HEAD_LEFT)
	{
		m_tInfo.vPos.x = m_pEnemy->GetInfo()->vPos.x - 15.f;
		m_tInfo.vPos.y = m_pEnemy->GetInfo()->vPos.y;
	}
	else if (m_dwState == HEAD_RIGHT)
	{
		m_tInfo.vPos.x = m_pEnemy->GetInfo()->vPos.x + 15.f;
		m_tInfo.vPos.y = m_pEnemy->GetInfo()->vPos.y;
	}



	m_fFramespeed = m_pEnemy->GetTear();

	bInvincible = *(m_pEnemy->GetInvincible());
	StateKeyInput();
	CEnemy::WorldMatrix();
	//cout << "head X : " << m_tInfo.vPos.x << endl;
	//cout << "head Y : " << m_tInfo.vPos.y << endl;
	if (bInvincible == true)
	{
		if (m_dwTime + 3000 < GetTickCount())
		{
			bInvincible = false;
			m_dwTime = GetTickCount();
		}
	}
	return 0;
}

void CEnemy_Head::Render(void)
{
	CEnemy::Render();
}

void CEnemy_Head::Release(void)
{

}
void CEnemy_Head::FrameMove(void)
{


	switch (m_dwState)
	{
	case HEAD_DOWN:
		m_tFrame = FRAME(0.f, 0.f, 4.f);
		break;
	case HEAD_UP:
		m_tFrame = FRAME(2.f, 0.f, 4.f);
		break;
	case HEAD_LEFT:
		m_tFrame = FRAME(3.f, 0.f, 4.f);
		break;
	case HEAD_RIGHT:
		m_tFrame = FRAME(1.f, 0.f, 4.f);
		break;
	}
	m_tStartFrame = m_tFrame;



	m_tFrame.fFrame += m_tFrame.fCount * GET_TIME;

	if (m_tFrame.fFrame > m_tFrame.fMax)
	{
		if (m_tStartFrame.fFrame == 0)
		{
			m_tFrame.fFrame = m_tStartFrame.fFrame;
			m_bTearFired = false;
		}
		else
		{
			m_tFrame.fFrame = m_tStartFrame.fFrame - 1;
			m_bTearFired = false;
		}
	}

}

void CEnemy_Head::StateKeyInput(void)
{
	srand((unsigned)time(NULL));
	if (KeyMgr_Song::GetInstance()->GetKeyState(VK_UP))
	{
		m_dwState = HEAD_UP;
		if (m_bTearFired == false)
		{
			if (rand() % 2 == 0)
				CSoundMgr::GetInst()->PlaySkillSound(L"tearfire1.wav");
			else
				CSoundMgr::GetInst()->PlaySkillSound(L"tearfire2.wav");


			CObj* pObj = CObjFactory<CTear>::CreateObj(m_tInfo.vPos, WAY_UP);
			pObj->m_PlayerID = m_pEnemy->m_PlayerID;
			CObjMgr::GetInst()->AddObj(OBJ_TEAR, pObj);
			m_bTearFired = true;
		}
	}

	if (KeyMgr_Song::GetInstance()->GetKeyState(VK_DOWN))
	{
		m_dwState = HEAD_DOWN;
		if (m_bTearFired == false)
		{
			if (rand() % 2 == 0)
				CSoundMgr::GetInst()->PlaySkillSound(L"tearfire1.wav");
			else
				CSoundMgr::GetInst()->PlaySkillSound(L"tearfire2.wav");

			CObj* pObj = CObjFactory<CTear>::CreateObj(m_tInfo.vPos, WAY_DOWN);
			pObj->m_PlayerID = m_pEnemy->m_PlayerID;
			CObjMgr::GetInst()->AddObj(OBJ_TEAR, pObj);
			m_bTearFired = true;
		}
	}

	if (KeyMgr_Song::GetInstance()->GetKeyState(VK_LEFT))
	{
		m_dwState = HEAD_LEFT;
		if (m_bTearFired == false)
		{
			if (rand() % 2 == 0)
				CSoundMgr::GetInst()->PlaySkillSound(L"tearfire1.wav");
			else
				CSoundMgr::GetInst()->PlaySkillSound(L"tearfire2.wav");

			CObj* pObj = CObjFactory<CTear>::CreateObj(m_tInfo.vPos, WAY_LEFT);
			pObj->m_PlayerID = m_pEnemy->m_PlayerID;
			CObjMgr::GetInst()->AddObj(OBJ_TEAR, pObj);
			m_bTearFired = true;
		}
	}

	if (KeyMgr_Song::GetInstance()->GetKeyState(VK_RIGHT))
	{
		m_dwState = HEAD_RIGHT;
		if (m_bTearFired == false)
		{
			if (rand() % 2 == 0)
				CSoundMgr::GetInst()->PlaySkillSound(L"tearfire1.wav");
			else
				CSoundMgr::GetInst()->PlaySkillSound(L"tearfire2.wav");


			CObj* pObj = CObjFactory<CTear>::CreateObj(m_tInfo.vPos, WAY_RIGHT);
			pObj->m_PlayerID = m_pEnemy->m_PlayerID;
			CObjMgr::GetInst()->AddObj(OBJ_TEAR, pObj);
			m_bTearFired = true;
		}
	}
}
