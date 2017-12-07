#include "StdAfx.h"
#include "Enemy_Body.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "KeyMgr_Song.h"

CEnemy_Body::CEnemy_Body(void)
{
	pObjList = CObjMgr::GetInst()->GetObjList();
}

CEnemy_Body::~CEnemy_Body(void)
{
	Release();
}

HRESULT CEnemy_Body::Initialize(void)
{
	m_wstrObjKey = L"Player";
	m_wstrStateKey = L"Body";
	m_dwState = BODY_DOWN;
	m_dwPrevState = BODY_DOWN;
	m_tFrame = FRAME(0.f, 0.f, 1.f);
	m_RenderType = R_WORLDOBJ_BODY;
	return S_OK;
}

int CEnemy_Body::Progress(void)
{

	FrameMove();
	m_tInfo.vPos = m_pEnemy->GetInfo()->vPos;
	bInvincible = *(m_pEnemy->GetInvincible());
	//StateKeyInput();
	CEnemy::WorldMatrix();
	if (bInvincible == true)
	{
		if (m_dwTime + 3000 < GetTickCount())
		{
			bInvincible = false;
			m_dwTime = GetTickCount();
		}
	}
	//cout << "body X : " << m_tInfo.vPos.x << endl;
	//cout << "body Y : " << m_tInfo.vPos.y << endl;
	return 0;
}

void CEnemy_Body::Render(void)
{
	CEnemy::Render();
}

void CEnemy_Body::Release(void)
{

}
void CEnemy_Body::FrameMove(void)
{

	switch (m_dwState)
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

	if (m_tFrame.fFrame > m_tFrame.fMax)
	{
		m_tFrame.fFrame = 0.f;
	}

}
void CEnemy_Body::StateKeyInput(void)
{
	if (KeyMgr_Song::GetInstance()->GetKeyState('W'))
	{
		m_dwState = BODY_UP;
	}

	else if (KeyMgr_Song::GetInstance()->GetKeyState('S'))
	{
		m_dwState = BODY_DOWN;
	}

	else if (KeyMgr_Song::GetInstance()->GetKeyState('A'))
	{
		m_dwState = BODY_LEFT;
	}

	else if (KeyMgr_Song::GetInstance()->GetKeyState('D'))
	{
		m_dwState = BODY_RIGHT;
	}
}




