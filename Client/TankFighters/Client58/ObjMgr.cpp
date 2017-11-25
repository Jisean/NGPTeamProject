#include "StdAfx.h"
#include "ObjMgr.h"
#include "BackGround.h"
#include "Player.h"
#include "ObjFactory.h"
#include "SoundMgr.h"

IMPLEMENT_SINGLETON(CObjMgr)




CObjMgr::CObjMgr(void)
{
}

CObjMgr::~CObjMgr(void)
{
	Release();
}

HRESULT CObjMgr::Initialize(void)
{
	CObj*	pBackGround = CObjFactory<CBackGround>::CreateObj();
	m_ObjList[OBJ_BACK].push_back(pBackGround);
	pfx = 0.f;
	pfy = 0.f;


	return S_OK;
}

void CObjMgr::Progress(void)
{	
	int		iResult = 0;

	for(int i = 0; i < OBJ_END; ++i)
	{
		for(list<CObj*>::iterator	iter = m_ObjList[i].begin();
			iter != m_ObjList[i].end(); )
		{
			iResult = (*iter)->Progress();

			if(iResult == 1)
			{
				::Safe_Delete(*iter);
				iter = m_ObjList[i].erase(iter);
			}

			else
				++iter;
		}
	}

	TearCheck();
	BulletCheck();

	//PlayerCheck();


	Battle();


}

void CObjMgr::Render(void)
{
	for(int i = 0; i < OBJ_END; ++i)
	{
		for(list<CObj*>::iterator	iter = m_ObjList[i].begin(); iter != m_ObjList[i].end(); ++iter)
		{
			m_vecRender[(*iter)->GetRenderType()].push_back(*iter);
		}
	}
	sort(m_vecRender[R_WORLDOBJ].begin(),
		m_vecRender[R_WORLDOBJ].end(),
		CObjMgr::Compare);
	for(int i = 0; i < R_END; ++i)
	{
		for(int j = 0, iCnt = m_vecRender[i].size(); j < iCnt; ++j)
		{
			m_vecRender[i][j]->Render();
		}

		m_vecRender[i].clear();
	}

}

void CObjMgr::Release(void)
{
	for(int i = 0; i < OBJ_END; ++i)
	{
		for_each(m_ObjList[i].begin(), m_ObjList[i].end(), DELETEOBJ());
		m_ObjList[i].clear();
	}


}

void CObjMgr::AddObj(OBJID _eID, CObj* pObj)
{
	m_ObjList[_eID].push_back(pObj);
}

const vector<TILE*>* CObjMgr::GetTile(void)
{
	return ((CBackGround*)m_ObjList[OBJ_BACK].front())->GetTile();
}
bool CObjMgr::Compare(CObj* pDest, CObj* pSource)
{
	return pDest->GetInfo()->vPos.y < pSource->GetInfo()->vPos.y;
}



void CObjMgr::TearCheck(void) // ´«¹° Ãæµ¹
{
	//list<CObj*>::iterator iter = m_ObjList[OBJ_MONSTER].begin();		
	//for(iter; iter != m_ObjList[OBJ_MONSTER].end(); ++iter)
	//{
	//	if(m_ObjList[OBJ_TEAR].size() <= 0)
	//		break;

	//	list<CObj*>::iterator iter2 =m_ObjList[OBJ_TEAR].begin();

	//	float fWidth = (*iter)->GetInfo()->vPos.x - (*iter2)->GetInfo()->vPos.x;
	//	float fHeight = (*iter)->GetInfo()->vPos.y - (*iter2)->GetInfo()->vPos.y;
	//	float fDistance = (fWidth * fWidth) + (fHeight * fHeight);
	//	fDistance = sqrt(fDistance);
	//	/////////////////////////////////

	//	//cout << "Distance " << fDistance << endl;
	//	//cout << "x Distance " << (*iter)->GetInfo()->vSize.x / 2.f + (*iter2)->GetInfo()->vSize.x / 2.f << endl;
	//	//cout << "y Distance " << (*iter)->GetInfo()->vSize.y / 2.f + (*iter2)->GetInfo()->vSize.y / 2.f << endl;
	//	/////////////////////////////////
	//	if((*iter)->GetInfo()->vSize.x / 2.f + (*iter2)->GetInfo()->vSize.x / 2.f > fDistance)
	//	{
	//		FIREWAY fireway;
	//		fireway = FIREWAY(*((*iter2)->GetFireWay()));

	//		if(fireway == WAY_LEFT)
	//		{
	//			(*iter)->GetInfo()->vPos.x -= 15.f;
	//			(*iter)->SetMonHp(-1.f);
	//		}
	//		else if(fireway == WAY_RIGHT)
	//		{
	//			(*iter)->GetInfo()->vPos.x += 15.f;
	//			(*iter)->SetMonHp(-1.f);
	//		}
	//		else if(fireway == WAY_UP)
	//		{
	//			(*iter)->GetInfo()->vPos.y -= 15.f;
	//			(*iter)->SetMonHp(-1.f);
	//		}
	//		else if(fireway == WAY_DOWN)
	//		{
	//			(*iter)->GetInfo()->vPos.y += 15.f;
	//			(*iter)->SetMonHp(-1.f);
	//		}
	//		(*iter2)->SetDead();
	//	}
	//	else if((*iter)->GetInfo()->vSize.y / 2.f + (*iter2)->GetInfo()->vSize.y / 2.f > fDistance)
	//	{
	//		FIREWAY fireway;
	//		fireway = FIREWAY(*((*iter2)->GetFireWay()));
	//		if(fireway == WAY_LEFT)
	//		{
	//			(*iter)->GetInfo()->vPos.x -= 15.f;
	//			(*iter)->SetMonHp(-1.f);
	//		}
	//		else if(fireway == WAY_RIGHT)
	//		{
	//			(*iter)->GetInfo()->vPos.x += 15.f;
	//			(*iter)->SetMonHp(-1.f);
	//		}
	//		else if(fireway == WAY_UP)
	//		{
	//			(*iter)->GetInfo()->vPos.y -= 15.f;
	//			(*iter)->SetMonHp(-1.f);
	//		}
	//		else if(fireway == WAY_DOWN)
	//		{
	//			(*iter)->GetInfo()->vPos.y += 15.f;
	//			(*iter)->SetMonHp(-1.f);
	//		}
	//		(*iter2)->SetDead();
	//	}
	//}
}


void CObjMgr::BulletCheck(void)
{
	//srand((unsigned)time(NULL));
	//list<CObj*>::iterator iter = m_ObjList[OBJ_BULLET].begin();		
	//for(iter; iter != m_ObjList[OBJ_BULLET].end(); ++iter)
	//{
	//	if(m_ObjList[OBJ_BULLET].size() <= 0)
	//		break;

	//	list<CObj*>::iterator iter2 =m_ObjList[OBJ_PLAYER].begin();
	//	list<CObj*>::iterator iter2_head =m_ObjList[OBJ_PLAYER_HEAD].begin();
	//	list<CObj*>::iterator iter2_body =m_ObjList[OBJ_PLAYER_BODY].begin();

	//	float fWidth = (*iter)->GetInfo()->vPos.x - (*iter2)->GetInfo()->vPos.x;
	//	float fHeight = (*iter)->GetInfo()->vPos.y - (*iter2)->GetInfo()->vPos.y;
	//	float fDistance = (fWidth * fWidth) + (fHeight * fHeight);
	//	fDistance = sqrt(fDistance);
	//	/////////////////////////////////

	//	//cout << "Distance " << fDistance << endl;
	//	//cout << "x Distance " << (*iter)->GetInfo()->vSize.x / 2.f + (*iter2)->GetInfo()->vSize.x / 2.f << endl;
	//	//cout << "y Distance " << (*iter)->GetInfo()->vSize.y / 2.f + (*iter2)->GetInfo()->vSize.y / 2.f << endl;
	//	/////////////////////////////////
	//	if((*iter)->GetInfo()->vSize.x / 2.f + (*iter2)->GetInfo()->vSize.x / 2.f > fDistance && *(*iter2)->GetInvincible() == false)
	//	{
	//		if(rand()%2 ==0)
	//			CSoundMgr::GetInst()->EffectSound1(L"playerhit1.wav");
	//		else
	//			CSoundMgr::GetInst()->EffectSound1(L"playerhit2.wav");
	//		(*iter2)->SetHP(-0.5f);
	//		(*iter2)->SetInvincible();
	//		(*iter2_body)->SetInvincible();
	//		(*iter2_head)->SetInvincible();
	//		(*iter)->SetDead();
	//	}
	//	else if((*iter)->GetInfo()->vSize.y / 2.f + (*iter2)->GetInfo()->vSize.y / 2.f > fDistance && *(*iter2)->GetInvincible() == false)
	//	{
	//		if(rand()%2 ==0)
	//			CSoundMgr::GetInst()->EffectSound1(L"playerhit1.wav");
	//		else
	//			CSoundMgr::GetInst()->EffectSound1(L"playerhit2.wav");
	//		(*iter2)->SetHP(-0.5f);
	//		(*iter2)->SetInvincible();
	//		(*iter2_body)->SetInvincible();
	//		(*iter2_head)->SetInvincible();
	//		(*iter)->SetDead();
	//	}
	//}
}


void CObjMgr::Battle(void)
{
	if (CObjMgr::GetInst()->GetObjList()[OBJ_TEAR].empty() == true)
		return;

	auto iterPlayer = CObjMgr::GetInst()->GetObjList()[OBJ_PLAYER].begin();

	CObj* pPlayer = *iterPlayer;

	++iterPlayer;
	if (iterPlayer == CObjMgr::GetInst()->GetObjList()[OBJ_PLAYER].end())
		return;

	CObj* pOtherPlayer = *iterPlayer;

	auto iter = CObjMgr::GetInst()->GetObjList()[OBJ_TEAR].begin();
	auto iter_end = CObjMgr::GetInst()->GetObjList()[OBJ_TEAR].end();

	for (iter; iter != iter_end; ++iter)
	{
		if ((*iter)->m_PlayerID == PLAYER_2P)
		{
			float fTearCXY = 5.f;
			float PlayerCXY = 35.f;

			D3DXVECTOR3 vTearPos = (*iter)->GetInfo()->vPos;
			D3DXVECTOR3 vPlayerPos = pPlayer->GetInfo()->vPos;;

			D3DXVECTOR3 vDistance = vPlayerPos - vTearPos;

			float fDistance = D3DXVec3Length(&vDistance);

			if (fDistance < fTearCXY + PlayerCXY + 3.f)
			{
				(*iter)->SetDead();
			}
		}

		else
		{
			float fTearCXY = 5.f;
			float PlayerCXY = 35.f;

			D3DXVECTOR3 vTearPos = (*iter)->GetInfo()->vPos;
			D3DXVECTOR3 vPlayerPos = pOtherPlayer->GetInfo()->vPos;;

			D3DXVECTOR3 vDistance = vPlayerPos - vTearPos;

			float fDistance = D3DXVec3Length(&vDistance);

			if (fDistance < fTearCXY + PlayerCXY + 3.f)
			{
				(*iter)->SetDead();
			}
		}
	}
}
