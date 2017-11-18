#include "StdAfx.h"
#include "HatCostume.h"
#include "AStar.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "KeyMgr_Song.h"
#include "ObjFactory.h"
#include "Player_Body.h"
#include "Tear.h"
CHatCostume::CHatCostume(void)
{
	pObjList = CObjMgr::GetInst()->GetObjList();
}

CHatCostume::~CHatCostume(void)
{
}
HRESULT CHatCostume::Initialize(void)
{
	m_wstrObjKey = L"ItemCostume";
	m_tFrame = FRAME(0.f, 1.f, 1.f);
	m_dwState = HEAD_STAND;
	m_dwPrevState = HEAD_STAND;
	m_tStartFrame = m_tFrame;
	m_fFramespeed = 2.f;
	m_bCostumeLoad = false;
	m_RenderType = R_WORLDOBJ_COSTUME_HAT;
	return S_OK;
}

int CHatCostume::Progress(void)
{
	if(m_bCostumeLoad == false)
	{
		if(m_dwState2 == PS_EPICFETUS)
			m_wstrStateKey = L"EpicFetus";

		m_bCostumeLoad = true;
	}
	FrameMove();
	list<CObj*>::iterator iter = pObjList[OBJ_PLAYER].begin();
	m_tInfo.vPos.x = (*iter)->GetInfo()->vPos.x + 1.f;
	m_tInfo.vPos.y = (*iter)->GetInfo()->vPos.y - 36.5f;
	bInvincible = *(*iter)->GetInvincible();
	m_fFramespeed = (*iter)->GetTear();
	StateKeyInput();
	CPlayer::WorldMatrix();
	return 0;
}

void CHatCostume::Render(void)
{
	CPlayer::Render();
}

void CHatCostume::Release(void)
{

}
void CHatCostume::FrameMove(void)
{
	
	if(m_dwState != m_dwPrevState)
	{
		switch(m_dwState)
		{
		case HEAD_STAND:
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
		}
		else
		{
			m_tFrame.fFrame = m_tStartFrame.fFrame - 1;
		}
	}

}

void CHatCostume::StateKeyInput(void)
{
	if(KeyMgr_Song::GetInstance()->GetKeyState(VK_UP))
	{
		m_dwState = HEAD_UP;
	}

	if(KeyMgr_Song::GetInstance()->GetKeyState(VK_DOWN))
	{
		m_dwState = HEAD_DOWN;
	}

	if(KeyMgr_Song::GetInstance()->GetKeyState(VK_LEFT))
	{
		m_dwState = HEAD_LEFT;
	}

	if(KeyMgr_Song::GetInstance()->GetKeyState(VK_RIGHT))
	{
		m_dwState = HEAD_RIGHT;
	}
}