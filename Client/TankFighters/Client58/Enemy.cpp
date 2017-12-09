#include "StdAfx.h"
#include "Enemy.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "KeyMgr_Song.h"
#include "ObjFactory.h"
#include "ObjMgr.h"
#include "Enemy_Body.h"
#include "Enemy_Head.h"
#include "SoundMgr.h"
#include "TimeMgr.h"

CEnemy::CEnemy(void)
{
}

CEnemy::~CEnemy(void)
{
	Release();
}

HRESULT CEnemy::Initialize(void)
{
	m_vecOffset = D3DXVECTOR3(500.f, 400.f, 0.f);
	m_tInfo.vSize = D3DXVECTOR3(50.f, 50.f, 0.f);
	m_RenderType = R_WORLDOBJ;
	m_RoomType = 0;
	m_bHasBodynHead = false;
	bInvincible = false;
	m_bBlinking = false;

	fSpeed = 200.f;

	return S_OK;
}

int CEnemy::Progress(void)
{

	if (m_bHasBodynHead == false)
	{
		CObj* pObj = CObjFactory<CEnemy_Body>::CreateObj(m_tInfo.vPos);
		dynamic_cast<CEnemy_Body*>(pObj)->m_pEnemy = this;

		CObjMgr::GetInst()->AddObj(OBJ_ENEMY_BODY, pObj);

		pObj = CObjFactory<CEnemy_Head>::CreateObj(m_tInfo.vPos.x, m_tInfo.vPos.y + 15.f);
		dynamic_cast<CEnemy_Head*>(pObj)->m_pEnemy = this;

		CObjMgr::GetInst()->AddObj(OBJ_ENEMY_HEAD, pObj);


		/*CObjMgr::GetInst()->AddObj(OBJ_Enemy_BODY, CObjFactory<CEnemy_Body>::CreateObj(m_tInfo.vPos));
		CObjMgr::GetInst()->AddObj(OBJ_Enemy_HEAD, CObjFactory<CEnemy_Head>::CreateObj(m_tInfo.vPos.x + 1, m_tInfo.vPos.y - 26.5f));*/

		m_bHasBodynHead = true;
	}

	WorldMatrix();

	//cout << "X : " << m_tInfo.vPos.x << endl;
	//cout << "Y : " << m_tInfo.vPos.y << endl;


	/*cout << "HP:"<< fHp << endl;
	cout << "MaxHP:" << iMaxHp << endl;*/
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

void CEnemy::Render(void)
{
	const TEXINFO* pTexture = m_pTexture->GetTexture(m_wstrObjKey, m_wstrStateKey, int(m_tFrame.fFrame));

	if (pTexture == NULL)
		return;

	float	fX = pTexture->tImgInfo.Width / 2.f;
	float	fY = pTexture->tImgInfo.Height / 2.f;

	m_pDevice->GetSprite()->SetTransform(&m_tInfo.matWorld);
	if (bInvincible == false)
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
void CEnemy::Release(void)
{
}


void CEnemy::WorldMatrix(void)
{
	D3DXMATRIX		matTrans;

	D3DXMatrixTranslation(&matTrans,
		m_tInfo.vPos.x + m_vScroll.x,
		m_tInfo.vPos.y + m_vScroll.y, 0.f);

	m_tInfo.matWorld = matTrans;
}


