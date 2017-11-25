#include "StdAfx.h"
#include "UI.h"
#include "ObjMgr.h"
#include "ObjFactory.h"
#include "HpUI.h"

CUI::CUI(void)
{
}

CUI::~CUI(void)
{
}

HRESULT	CUI::Initialize()
{
	m_bIsBossRoom = false;
	m_bIsDelete = false;
	m_bHasUI = false;
	m_RenderType = R_UI;
	return S_OK;
}

int CUI::Progress()
{
	if(m_bHasUI == false)
	{
		////////////////////////////////////////HPBAR/////////////////////////////////////////////
		list<CObj*>::iterator iter = CObjMgr::GetInst()->GetObjList()[OBJ_PLAYER].begin();
		m_iCount = *(*iter)->GetPlayerMaxHP();

		for(int i = 0; i < m_iCount; ++i)
		{
			CObjMgr::GetInst()->AddObj(OBJ_UI_HP,
				CObjFactory<CHpUI>::CreateObj(100.f + i * 22 ,50.f));
		}

		////////////////////////////////////////////////////////////////////////////////////////
		m_bHasUI = true;
	}

	WorldMatrix();
	return 0;
}

void CUI::Render()
{
	const TEXINFO* pTexture = m_pTexture->GetTexture(m_wstrObjKey, m_wstrStateKey, int(m_tFrame.fFrame));

	if(pTexture == NULL)
		return;

	float	fX = pTexture->tImgInfo.Width / 2.f;
	float	fY = pTexture->tImgInfo.Height / 2.f;

	m_pDevice->GetSprite()->SetTransform(&m_tInfo.matWorld);
	m_pDevice->GetSprite()->Draw(pTexture->pTexture, 
		NULL, &D3DXVECTOR3(fX, fY, 0.f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CUI::Release()
{
}
void CUI::WorldMatrix(void)
{
	D3DXMATRIX		matTrans;

	D3DXMatrixTranslation(&matTrans, 
		m_tInfo.vPos.x, 
		m_tInfo.vPos.y, 0.f);

	m_tInfo.matWorld = matTrans;
}
