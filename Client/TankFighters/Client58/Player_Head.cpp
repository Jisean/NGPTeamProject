#include "StdAfx.h"
#include "Player_Head.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "KeyMgr_Song.h"
#include "ObjFactory.h"
#include "Player_Body.h"
#include "Tear.h"
#include "SoundMgr.h"
CPlayer_Head::CPlayer_Head(void)
{
	pObjList = CObjMgr::GetInst()->GetObjList();
}

CPlayer_Head::~CPlayer_Head(void)
{
	Release();
}

HRESULT CPlayer_Head::Initialize(void)
{
	m_wstrObjKey = L"Player";
	m_wstrStateKey = L"Isaac_Head";
	m_tFrame = FRAME(0.f, 1.f, 1.f);
	m_dwState = HEAD_STAND;
	m_dwState2 = BODY_STAND;
	m_dwPrevState = HEAD_STAND;
	m_tStartFrame = m_tFrame;
	m_fFramespeed = 2.f;
	m_bTearFired = false;
	m_RenderType = R_WORLDOBJ_HEAD;
	return S_OK;
}

int CPlayer_Head::Progress(void)
{
	FrameMove();
	//list<CObj*>::iterator iter = pObjList[OBJ_PLAYER].begin();
	m_tInfo.vPos.x = m_pPlayer->GetInfo()->vPos.x + 1.f;
	m_tInfo.vPos.y = m_pPlayer->GetInfo()->vPos.y - 26.5f;



	m_fFramespeed = m_pPlayer->GetTear();

	bInvincible = *(m_pPlayer->GetInvincible());
	//bInvincible = *(*iter)->GetInvincible();
	StateKeyInput();
	CPlayer::WorldMatrix();
	//cout << "head X : " << m_tInfo.vPos.x << endl;
	//cout << "head Y : " << m_tInfo.vPos.y << endl;
	if(bInvincible == true)
	{
		if(m_dwTime + 3000 < GetTickCount())
		{
			bInvincible = false;
			m_dwTime = GetTickCount();
		}
	}
	return 0;
}

void CPlayer_Head::Render(void)
{
	CPlayer::Render();
}

void CPlayer_Head::Release(void)
{

}
void CPlayer_Head::FrameMove(void)
{
	
	if(m_dwState != m_dwPrevState)
	{
		switch(m_dwState)
		{
		case HEAD_STAND:
		/*	if(m_dwState2 == BODY_LEFT)
			{
				m_tFrame = FRAME(6.f, 0.f, 8.f);
			}
			if(m_dwState2 == BODY_RIGHT)
			{
				m_tFrame = FRAME(3.f, 0.f, 8.f);
			}*/
			m_tFrame = FRAME(0.f, 1.f, 1.f);
			break;
		case HEAD_DOWN:
			m_tFrame = FRAME(1.f, 2.f + m_fFramespeed, 2.f);
			break;
		case HEAD_UP:
			m_tFrame = FRAME(5.f, 2.f + m_fFramespeed, 6.f);
			break;
		case HEAD_LEFT:
			m_tFrame = FRAME(7.f, 2.f + m_fFramespeed, 8.f);
			break;
		case HEAD_RIGHT:
			m_tFrame = FRAME(3.f, 2.f + m_fFramespeed, 4.f);
			break;
		}
		m_tStartFrame = m_tFrame;
		m_dwPrevState = m_dwState;
	}

	
	m_tFrame.fFrame += m_tFrame.fCount * GET_TIME;

	if(m_tFrame.fFrame > m_tFrame.fMax)
	{
		if(m_dwState != HEAD_STAND)
		{
			m_dwState = HEAD_STAND;
		}
	
		if(m_tStartFrame.fFrame == 0)
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

void CPlayer_Head::StateKeyInput(void)
{
	srand((unsigned)time(NULL));
	if(KeyMgr_Song::GetInstance()->GetKeyState(VK_UP))
	{
		m_dwState = HEAD_UP;
		if(m_tFrame.fFrame < 6.f && m_tFrame.fFrame > 5.f && m_bTearFired == false)
		{
			if(rand()%2 == 0)
				CSoundMgr::GetInst()->PlaySkillSound(L"tearfire1.wav");
			else
				CSoundMgr::GetInst()->PlaySkillSound(L"tearfire2.wav");

			
				CObj* pObj = CObjFactory<CTear>::CreateObj(m_tInfo.vPos, WAY_UP);
				pObj->m_PlayerID = m_pPlayer->m_PlayerID;
				CObjMgr::GetInst()->AddObj(OBJ_TEAR, pObj);
			m_bTearFired = true;
		}
	}

	if(KeyMgr_Song::GetInstance()->GetKeyState(VK_DOWN))
	{
		m_dwState = HEAD_DOWN;
		if(m_tFrame.fFrame < 2.f && m_tFrame.fFrame > 1.f && m_bTearFired == false)
		{
			if(rand()%2 == 0)
				CSoundMgr::GetInst()->PlaySkillSound(L"tearfire1.wav");
			else
				CSoundMgr::GetInst()->PlaySkillSound(L"tearfire2.wav");	
				
			CObj* pObj = CObjFactory<CTear>::CreateObj(m_tInfo.vPos, WAY_DOWN);
			pObj->m_PlayerID = m_pPlayer->m_PlayerID;
			CObjMgr::GetInst()->AddObj(OBJ_TEAR, pObj);
			m_bTearFired = true;
		}
	}

	if(KeyMgr_Song::GetInstance()->GetKeyState(VK_LEFT))
	{
		m_dwState = HEAD_LEFT;
		if(m_tFrame.fFrame < 8.f && m_tFrame.fFrame > 7.f && m_bTearFired == false)
		{
			if(rand()%2 == 0)
				CSoundMgr::GetInst()->PlaySkillSound(L"tearfire1.wav");
			else
				CSoundMgr::GetInst()->PlaySkillSound(L"tearfire2.wav");
			
				CObj* pObj = CObjFactory<CTear>::CreateObj(m_tInfo.vPos, WAY_LEFT);
				pObj->m_PlayerID = m_pPlayer->m_PlayerID;
				CObjMgr::GetInst()->AddObj(OBJ_TEAR, pObj);
			m_bTearFired = true;
		}
	}

	if(KeyMgr_Song::GetInstance()->GetKeyState(VK_RIGHT))
	{
		m_dwState = HEAD_RIGHT;
		if(m_tFrame.fFrame < 4.f && m_tFrame.fFrame > 3.f && m_bTearFired == false)
		{
			if(rand()%2 == 0)
				CSoundMgr::GetInst()->PlaySkillSound(L"tearfire1.wav");
			else
				CSoundMgr::GetInst()->PlaySkillSound(L"tearfire2.wav");
			
			
				CObj* pObj = CObjFactory<CTear>::CreateObj(m_tInfo.vPos, WAY_RIGHT);
				pObj->m_PlayerID = m_pPlayer->m_PlayerID;
				CObjMgr::GetInst()->AddObj(OBJ_TEAR, pObj);
			m_bTearFired = true;
		}
	}
}
