#include "StdAfx.h"
#include "Player_Body.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "KeyMgr_Song.h"

CPlayer_Body::CPlayer_Body(void)
{
	pObjList = CObjMgr::GetInst()->GetObjList();
}

CPlayer_Body::~CPlayer_Body(void)
{
	Release();
}

HRESULT CPlayer_Body::Initialize(void)
{
	m_wstrObjKey = L"Player";
	m_wstrStateKey = L"Body";
	m_dwState = BODY_DOWN;
	m_dwPrevState = BODY_DOWN;
	m_tFrame = FRAME(0.f, 0.f, 1.f);
	m_RenderType = R_WORLDOBJ_BODY;
	return S_OK;
}

int CPlayer_Body::Progress(void)
{

	FrameMove();
	m_tInfo.vPos = m_pPlayer->GetInfo()->vPos;
	bInvincible = *(m_pPlayer->GetInvincible());
	CPlayer::WorldMatrix();
	if(bInvincible == true)
	{
		if(m_dwTime + 3000 < GetTickCount())
		{
			bInvincible = false;
			m_dwTime = GetTickCount();
		}
	}
	//cout << "body X : " << m_tInfo.vPos.x << endl;
	//cout << "body Y : " << m_tInfo.vPos.y << endl;
	return 0;
}

void CPlayer_Body::Render(void)
{
	CPlayer::Render();
}

void CPlayer_Body::Release(void)
{

}
void CPlayer_Body::FrameMove(void)
{

		switch(m_dwState)
		{
		case BODY_UP:
			m_wstrStateKey = L"Body_Up";
			m_tFrame = FRAME(0.f, 0.f, 1.f);
			break;
		case BODY_DOWN:
			m_wstrStateKey = L"Body_Down";
			m_tFrame = FRAME(0.f, 0.f, 1.f);
			break;
		case BODY_LEFT:
			m_wstrStateKey = L"Body_Left";
			m_tFrame = FRAME(0.f, 0.f, 1.f);
			break;
		case BODY_RIGHT:
			m_wstrStateKey = L"Body_Right";
			m_tFrame = FRAME(0.f, 0.f, 1.f);
			break;
		}
	

	
	m_tFrame.fFrame += m_tFrame.fCount * GET_TIME;

	if(m_tFrame.fFrame > m_tFrame.fMax)
	{
		m_tFrame.fFrame = 0.f;
	}

}
void CPlayer_Body::StateKeyInput(KEY& KeyValue)
{
	if (KeyValue.bUp)
	{
		m_dwState = BODY_UP;
	}

	else if (KeyValue.bDown)
	{
		m_dwState = BODY_DOWN;
	}

	else if(KeyValue.bLeft)
	{
		m_dwState = BODY_LEFT;
	}

	else if(KeyValue.bRight)
	{
		m_dwState = BODY_RIGHT;
	}
}




