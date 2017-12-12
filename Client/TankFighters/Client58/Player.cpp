#include "StdAfx.h"
#include "Player.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "KeyMgr_Song.h"
#include "ObjFactory.h"
#include "ObjMgr.h"
#include "Player_Body.h"
#include "Player_Head.h"
#include "SoundMgr.h"
#include "TimeMgr.h"

CPlayer::CPlayer(void)
{
}

CPlayer::~CPlayer(void)
{
	Release();
}

HRESULT CPlayer::Initialize(void)
{
	m_vecOffset = D3DXVECTOR3(500.f, 400.f, 0.f);
	m_tInfo.vSize = D3DXVECTOR3(50.f, 50.f, 0.f);
	m_RenderType = R_WORLDOBJ;
	m_RoomType = 0;
	m_bHasBodynHead = false;
	bInvincible = false;
	m_bBlinking = false;
	StatLoad(L"Isaac");

	fSpeed = 200.f;

	return S_OK;
}

int CPlayer::Progress(void)
{

	if(m_bHasBodynHead == false)
	{
		CObj* pObj = CObjFactory<CPlayer_Body>::CreateObj(m_tInfo.vPos);
		dynamic_cast<CPlayer_Body*>(pObj)->m_pPlayer = this;

		CObjMgr::GetInst()->AddObj(OBJ_PLAYER_BODY, pObj);

		pObj = CObjFactory<CPlayer_Head>::CreateObj(m_tInfo.vPos.x, m_tInfo.vPos.y + 15.f);
		dynamic_cast<CPlayer_Head*>(pObj)->m_pPlayer = this;

		CObjMgr::GetInst()->AddObj(OBJ_PLAYER_HEAD, pObj);


		/*CObjMgr::GetInst()->AddObj(OBJ_PLAYER_BODY, CObjFactory<CPlayer_Body>::CreateObj(m_tInfo.vPos));
		CObjMgr::GetInst()->AddObj(OBJ_PLAYER_HEAD, CObjFactory<CPlayer_Head>::CreateObj(m_tInfo.vPos.x + 1, m_tInfo.vPos.y - 26.5f));*/

		m_bHasBodynHead = true;
	}

	WorldMatrix();
	KeyInput();
	Scroll();

	//cout << "X : " << m_tInfo.vPos.x << endl;
	//cout << "Y : " << m_tInfo.vPos.y << endl;


	/*cout << "HP:"<< fHp << endl;
	cout << "MaxHP:" << iMaxHp << endl;*/
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

void CPlayer::Render(void)
{
	const TEXINFO* pTexture = m_pTexture->GetTexture(m_wstrObjKey, m_wstrStateKey, int(m_tFrame.fFrame));

	if(pTexture == NULL)
		return;

	float	fX = pTexture->tImgInfo.Width / 2.f;
	float	fY = pTexture->tImgInfo.Height / 2.f;

	m_pDevice->GetSprite()->SetTransform(&m_tInfo.matWorld);
	if(bInvincible == false)
	{
	m_pDevice->GetSprite()->Draw(pTexture->pTexture, 
		NULL, &D3DXVECTOR3(fX, fY, 0.f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	else
	{
		m_pDevice->GetSprite()->Draw(pTexture->pTexture, 
			NULL, &D3DXVECTOR3(fX, fY, 0.f), NULL, D3DCOLOR_ARGB(155, 255, 255, 255));

	}
}
void CPlayer::Release(void)
{
}


void CPlayer::WorldMatrix(void)
{
	D3DXMATRIX		matTrans;

	D3DXMatrixTranslation(&matTrans, 
		m_tInfo.vPos.x + m_vScroll.x, 
		m_tInfo.vPos.y + m_vScroll.y, 0.f);

	m_tInfo.matWorld = matTrans;
}

void CPlayer::KeyInput(void)
{
	/*if(KeyMgr_Song::GetInstance()->GetKeyState('W'))
	{
		m_tInfo.vPos.y -= fSpeed * CTimeMgr::GetInst()->GetTime();
	}

	if(KeyMgr_Song::GetInstance()->GetKeyState('S'))
	{
		m_tInfo.vPos.y += fSpeed * CTimeMgr::GetInst()->GetTime();
	}

	if(KeyMgr_Song::GetInstance()->GetKeyState('A'))
	{
		m_tInfo.vPos.x -= fSpeed * CTimeMgr::GetInst()->GetTime();
	}

	if(KeyMgr_Song::GetInstance()->GetKeyState('D'))
	{
		m_tInfo.vPos.x += fSpeed * CTimeMgr::GetInst()->GetTime();

	}*/
	/*if(CKeyMgr::GetInst()->KeyPressed(KEY_CTRL))
	{
		if(iBombs > 0)
		{
			--iBombs;
			CSoundMgr::GetInst()->PlaySkillSound(L"bombset.wav");
			CObjMgr::GetInst()->AddObj(OBJ_BOMB, CObjFactory<CBomb>::CreateObj(m_tInfo.vPos));
		}
	}*/

	/*if(CKeyMgr::GetInst()->KeyPressed(KEY_1))
	{
		fHp += 0.5f;
	}
	if(CKeyMgr::GetInst()->KeyPressed(KEY_2))
	{
		fHp -= 0.5f;
	}
	if(CKeyMgr::GetInst()->KeyPressed(KEY_3))
	{
		++iMaxHp;
	}
	if(CKeyMgr::GetInst()->KeyPressed(KEY_4))
	{
		--iMaxHp;
	}*/

}


void CPlayer::Scroll(void)
{
	//플레이어x랑 스크롤을 더한 값이
	//화면 중앙 + 오프셋보다 커졌을 떄 (오른쪽)

	const TEXINFO* pTexture = m_pTexture->GetTexture(L"BASEMENT", L"Basement",NULL);

	if(m_tInfo.vPos.x + m_vScroll.x > WINCX / 2 + m_vecOffset.x)
	{
		//스크롤 값을 빼준다..
		for(float f=0.f; f < 108.7 ; f += 0.1f)
		{
			m_vScroll.x -= int(1.f);
		}

		//그려야 되는 이미지를 넘어가려고 하면 고정시킨다.
		if(m_vScroll.x > (float)pTexture->tImgInfo.Width - WINCX)
			m_vScroll.x = (float)pTexture->tImgInfo.Width - WINCX;
	}
	if(m_tInfo.vPos.x + m_vScroll.x < WINCX / 2 - m_vecOffset.x)
	{
		for(float f=0.f; f < 108.7 ; f += 0.1f)
		{
			m_vScroll.x += int(1.f);
		}

		if(m_vScroll.x > 0)
			m_vScroll.x = 0;
	}
	if(m_tInfo.vPos.y + m_vScroll.y > WINCY / 2 + m_vecOffset.y)
	{
		for(float f=0.f; f < 75.8 ; f += 0.1f)
			m_vScroll.y -= int(1.f);

		if(m_vScroll.y > (float)pTexture->tImgInfo.Height - WINCY)
			m_vScroll.y = (float) pTexture->tImgInfo.Height - WINCY;
	}
	if(m_tInfo.vPos.y  + m_vScroll.y < WINCY / 2 - m_vecOffset.y)
	{
		for(float f=0.f; f < 75.8 ; f += 0.1f)
			m_vScroll.y += int(1.f);

		if(m_vScroll.y > 0)
			m_vScroll.y = 0;
	}
}
void CPlayer::StatLoad(const wstring& wstrName)
{
	fAttack = 3.0f;
	fHp = 3.0f;
	iMaxHp = 3;
	fTears = 3.0f;
	fShotSpeed = 3.0f;
	fSpeed = 1.f;
	fRange = 3.f;
	iLuck = 1;
	iCoins = 1;
	iKeys = 1;
	iBombs = 1;

}


