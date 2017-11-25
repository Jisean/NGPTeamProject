#include "StdAfx.h"
#include "TileMgr.h"
#include "ObjMgr.h"
#include "BackGround.h"
#include "KeyMgr_Song.h"
#include "ObjFactory.h"
#include <time.h>
#include "SoundMgr.h"
#include "TimeMgr.h"

IMPLEMENT_SINGLETON(CTileMgr)

CTileMgr::CTileMgr(void)
{
	pObjList = CObjMgr::GetInst()->GetObjList();

	b_DoorSound1 = false;
	b_DoorSound2 = false;
	b_DoorSound3 = false;
	b_DoorSound4 = false;
	b_DoorSound5 = false;

}

CTileMgr::~CTileMgr(void)
{

}


void CTileMgr::Progress(void)
{
	PlayerTile();
	TearTile();
	//BulletTile();
	//DoorTile();
	//BombTile();

	if (m_bTile == false)
	{
		m_bTile = true;

		vector<TILE*>::const_iterator tileiter = CObjMgr::GetInst()->GetTile()->begin();
		vector<TILE*>::const_iterator tileiter_end = CObjMgr::GetInst()->GetTile()->end();

		for (tileiter; tileiter != tileiter_end; ++tileiter)
		{
			TILE* pTile = *tileiter;
			if (pTile->byOption == 1 || pTile->byOption == 3 || pTile->byOption == 4)
			{
				m_vecNonMoveTile.push_back(pTile);
			}
		}
	}

}
void CTileMgr::PlayerTile(void)
{
	list<CObj*>::iterator iter = pObjList[OBJ_PLAYER].begin();
	list<CObj*>::iterator iter_end = pObjList[OBJ_PLAYER].end();

	for (iter; iter != iter_end; ++iter)
	{
		CObj* pPlayer = *iter;

		vector<TILE*>::iterator tileiter = m_vecNonMoveTile.begin();
		vector<TILE*>::iterator tileiter_end = m_vecNonMoveTile.end();

		for (tileiter; tileiter != tileiter_end; tileiter++)
		{
			TILE* pTile = *tileiter;

			if (pTile->byOption == 1 || pTile->byOption == 3 || pTile->byOption == 4)
			{
				D3DXVECTOR3 vDis = pTile->vPos - pPlayer->GetInfo()->vPos;
				float fDis = D3DXVec3Length(&vDis);

				D3DXVECTOR3 vDir = vDis;
				D3DXVec3Normalize(&vDir, &vDir);

				float fCheckValue; // ¹Ú½ºÀÇ Å©±â

				if (pTile->byOption == 1)
					fCheckValue = 100.f;

				else
					fCheckValue = 50.f;

				if (fDis < fCheckValue + 30.f)
				{
					D3DXVECTOR3 vPlayerPos = pPlayer->GetInfo()->vPos;
					D3DXVECTOR3 vTilePos = pTile->vPos;

					RECT rcPlayer;
					rcPlayer.top = vPlayerPos.y - fCheckValue / 2;
					rcPlayer.bottom = vPlayerPos.y + fCheckValue / 2;
					rcPlayer.left = vPlayerPos.x - fCheckValue / 2;
					rcPlayer.right = vPlayerPos.x + fCheckValue / 2;

					RECT rcSource;
					rcSource.top = vTilePos.y - fCheckValue / 2;
					rcSource.bottom = vTilePos.y + fCheckValue / 2;
					rcSource.left = vTilePos.x - fCheckValue / 2;
					rcSource.right = vTilePos.x + fCheckValue / 2;

					RECT rc;

					if (IntersectRect(&rc, &rcPlayer, &rcSource))
					{
						SetRect(&rc, 0, 0, rc.right - rc.left, rc.bottom - rc.top);

						if (rc.bottom > rc.right) // ÁÂ¿ì Ãæµ¹
						{
							if (pPlayer->GetInfo()->vPos.x < pTile->vPos.x)
							{
								pPlayer->GetInfo()->vPos.x = pPlayer->GetInfo()->vPos.x - rc.right;
							}

							else if (pPlayer->GetInfo()->vPos.x > pTile->vPos.x)
							{
								pPlayer->GetInfo()->vPos.x = pPlayer->GetInfo()->vPos.x + rc.right;
							}
						}

						if (rc.bottom < rc.right)
						{
							if (pPlayer->GetInfo()->vPos.y < pTile->vPos.y)
							{
								pPlayer->GetInfo()->vPos.y = pPlayer->GetInfo()->vPos.y - rc.bottom;
							}

							else if (pPlayer->GetInfo()->vPos.y > pTile->vPos.y)
							{
								pPlayer->GetInfo()->vPos.y = pPlayer->GetInfo()->vPos.y + rc.bottom;
							}
						}
					}
				}




			}
		}
	}


}

void CTileMgr::TearTile(void)
{
	if (CObjMgr::GetInst()->GetObjList()[OBJ_TEAR].empty() == true)
		return;


	list<CObj*>::iterator iter = pObjList[OBJ_TEAR].begin();
	list<CObj*>::iterator iter_end = pObjList[OBJ_TEAR].end();

	for (iter; iter != iter_end; ++iter)
	{
		auto iter_Tile = m_vecNonMoveTile.begin();
		auto iter_Tile_end = m_vecNonMoveTile.end();

		for (iter_Tile; iter_Tile != iter_Tile_end; ++iter_Tile)
		{
			float fTearCXY = 5.f;
			float fTileCXY = 35.f;
			
			D3DXVECTOR3 vTearPos = (*iter)->GetInfo()->vPos;
			D3DXVECTOR3 vTilePos = (*iter_Tile)->vPos;

			D3DXVECTOR3 vDistance = vTearPos - vTilePos;

			float fDistance = D3DXVec3Length(&vDistance);

			if (fDistance < fTearCXY + fTileCXY + 3.f)
			{
				(*iter)->SetDead();
			}

		}
	}


	
}
void CTileMgr::MonsterTile(void)
{
	//list<CObj*>::iterator iter = pObjList[OBJ_MONSTER].begin();
	//list<CObj*>::iterator iter_end = pObjList[OBJ_MONSTER].end();

	//vector<TILE*>::const_iterator tileiter = CObjMgr::GetInst()->GetTile()->begin();
	//vector<TILE*>::const_iterator tileiter_end = CObjMgr::GetInst()->GetTile()->end();

	//for (iter; iter != iter_end; ++iter)
	//{
	//	for (tileiter; tileiter != tileiter_end; ++tileiter)
	//	{

	//		float fWidth = (*iter)->GetInfo()->vSize.x - 3 / 2.f + (*tileiter)->vSize.x / 2.f;
	//		float fHeight = (*iter)->GetInfo()->vSize.y / 2.f + (*tileiter)->vSize.y / 2.f;

	//		float fDistX = fabs((*iter)->GetInfo()->vPos.x - (*tileiter)->vPos.x);
	//		float fDistY = fabs((*iter)->GetInfo()->vPos.y - (*tileiter)->vPos.y);

	//		if (pmonsterfx != NULL && pmonsterfy != NULL)
	//		{
	//			pmonsterfx = fWidth - fDistX;
	//			pmonsterfy = fHeight - fDistY;
	//		}

	//		if (fDistX < fWidth && fDistY < fHeight)
	//		{
	//			//0. ÀÌµ¿°¡´É 1. ÀÌµ¿ºÒ°¡ 2.°¡½Ã 3.X 4.µ¹ 
	//			//5.ºÒ 6.º® 7.´ÝÈù ¿Þ¹® 8.¿­¸° ¿Þ¹® 9.´ÝÈù ¿À¸¥¹® 
	//			//10.¿­¸° ¿À¸¥¹® 11. ´ÝÈù À­¹® 12.¿­¸° À­¹® 13.´ÝÈù ¾Æ·§¹® 14.¿­¸° ¾Æ·§¹®
	//			if ((*tileiter)->byOption == 0)
	//			{
	//				(*tileiter)->byOption = 1;
	//			}
	//			if ((*tileiter)->byOption == 3 ||
	//				(*tileiter)->byOption == 4 ||
	//				(*tileiter)->byOption == 6 ||
	//				(*tileiter)->byOption == 7 ||
	//				(*tileiter)->byOption == 9 ||
	//				(*tileiter)->byOption == 11 ||
	//				(*tileiter)->byOption == 13)
	//			{
	//				if (pmonsterfy > pmonsterfx)
	//				{
	//					//°¡·Î
	//					if ((*iter)->GetInfo()->vPos.x < (*tileiter)->vPos.x)
	//					{
	//						//¿ÞÂÊ
	//						//if(KeyMgr_Song::GetInstance()->GetKeyState('D'))
	//						(*iter)->GetInfo()->vPos.x -= (*iter)->GetInfo()->vDir.x;;
	//					}
	//					else
	//					{
	//						//¿À¸¥ÂÊ
	//						//if(KeyMgr_Song::GetInstance()->GetKeyState('A'))
	//						(*iter)->GetInfo()->vPos.x += (*iter)->GetInfo()->vDir.x;;
	//					}
	//				}
	//				else
	//				{
	//					//¼¼·Î
	//					if ((*iter)->GetInfo()->vPos.y < (*tileiter)->vPos.y)
	//					{
	//						//À§
	//						//if(KeyMgr_Song::GetInstance()->GetKeyState('S'))
	//						(*iter)->GetInfo()->vPos.y -= (*iter)->GetInfo()->vDir.y;;
	//					}
	//					else
	//					{
	//						//¾Æ·¡
	//						//if(KeyMgr_Song::GetInstance()->GetKeyState('W'))
	//						(*iter)->GetInfo()->vPos.y += (*iter)->GetInfo()->vDir.y;;
	//					}
	//				}
	//			}
	//			else
	//			{
	//				if ((*tileiter)->byOption == 1)
	//				{
	//					(*tileiter)->byOption = 0;
	//				}
	//			}
	//		}
	//	}
	//}
}

void CTileMgr::BulletTile(void)
{
	//list<CObj*>::iterator iter = pObjList[OBJ_BULLET].begin();
	//list<CObj*>::iterator iter_end = pObjList[OBJ_BULLET].end();

	//for (iter; iter != iter_end; iter++)
	//{
	//	if (pObjList[OBJ_BULLET].size() <= 0)
	//		return;
	//	vector<TILE*>::const_iterator tileiter = CObjMgr::GetInst()->GetTile()->begin();
	//	vector<TILE*>::const_iterator tileiter_end = CObjMgr::GetInst()->GetTile()->end();

	//	for (tileiter; tileiter != tileiter_end; tileiter++)
	//	{
	//		float fWidth = (*iter)->GetInfo()->vSize.x / 2.f - (*tileiter)->vSize.x / 2.f;
	//		float fHeight = (*iter)->GetInfo()->vSize.y / 2.f + (*tileiter)->vSize.y / 2.f;

	//		float fDistX = fabs((*iter)->GetInfo()->vPos.x - (*tileiter)->vPos.x);
	//		float fDistY = fabs((*iter)->GetInfo()->vPos.y - (*tileiter)->vPos.y);

	//		if (pbulletfx != NULL && pbulletfy != NULL)
	//		{
	//			pbulletfx = fWidth - fDistX;
	//			pbulletfy = fHeight - fDistY;
	//		}

	//		if (fDistX < fWidth && fDistY < fHeight)
	//		{
	//			if ((*tileiter)->byOption == 0)
	//				continue;

	//			else if ((*tileiter)->byOption == 2)
	//				continue;



	//			//0. ÀÌµ¿°¡´É 1. ÀÌµ¿ºÒ°¡ 2.°¡½Ã 3.¶Ë 4.µ¹ 
	//			//5.ºÒ 6.º® 7.´ÝÈù ¿Þ¹® 8.¿­¸° ¿Þ¹® 9.´ÝÈù ¿À¸¥¹® 
	//			//10.¿­¸° ¿À¸¥¹® 11. ´ÝÈù À­¹® 12.¿­¸° À­¹® 13.´ÝÈù ¾Æ·§¹® 14.¿­¸° ¾Æ·§¹®
	//			if ((*tileiter)->byOption == 1 ||
	//				(*tileiter)->byOption == 3 ||
	//				(*tileiter)->byOption == 4)
	//			{
	//				if (pbulletfy > pbulletfx)
	//				{
	//					//°¡·Î
	//					if ((*iter)->GetInfo()->vPos.x < (*tileiter)->vPos.x)
	//					{
	//						//¿ÞÂÊ
	//						(*iter)->SetDead();
	//					}
	//					else
	//					{
	//						(*iter)->SetDead();
	//					}
	//				}
	//				else
	//				{
	//					//¼¼·Î
	//					if ((*iter)->GetInfo()->vPos.y < (*tileiter)->vPos.y)
	//					{
	//						//À§
	//						(*iter)->SetDead();
	//					}
	//					else
	//					{
	//						//¾Æ·¡
	//						(*iter)->SetDead();
	//					}
	//				}

	//			}
	//		}
	//	}
	//}
}
void CTileMgr::DoorTile(void)
{
	/*list<CObj*>::iterator iter = pObjList[OBJ_PLAYER].begin();
	vector<TILE*>::const_iterator tileiter = CObjMgr::GetInst()->GetTile()->begin();
	vector<TILE*>::const_iterator tileiter_end = CObjMgr::GetInst()->GetTile()->end();

	if (*(*iter)->GetRoomType() == 1)
	{
		if (g_iRoomMobCnt1 == 0)
		{
			for (int i = 0; i < 522; ++i)
			{
				++tileiter;
			}
			(*tileiter)->byDrawID = 13;
			(*tileiter)->byOption = 8;

			tileiter = CObjMgr::GetInst()->GetTile()->begin();
			for (int i = 0; i < 535; ++i)
			{
				++tileiter;
			}
			(*tileiter)->byDrawID = 15;
			(*tileiter)->byOption = 10;

			if (b_DoorSound1 == false)
			{
				CSoundMgr::GetInst()->EffectSound4(L"dooropen.wav");
				b_DoorSound1 = true;
			}

		}
	}
	else if (*(*iter)->GetRoomType() == 2)
	{
		if (g_iRoomMobCnt2 == -4)
		{
			for (int i = 0; i < 538; ++i)
			{
				++tileiter;
			}
			(*tileiter)->byDrawID = 13;
			(*tileiter)->byOption = 8;

			tileiter = CObjMgr::GetInst()->GetTile()->begin();
			for (int i = 0; i < 551; ++i)
			{
				++tileiter;
			}
			(*tileiter)->byDrawID = 15;
			(*tileiter)->byOption = 10;

			tileiter = CObjMgr::GetInst()->GetTile()->begin();
			for (int i = 0; i < 948; ++i)
			{
				++tileiter;
			}
			(*tileiter)->byDrawID = 11;
			(*tileiter)->byOption = 14;

			if (b_DoorSound2 == false)
			{
				CSoundMgr::GetInst()->EffectSound4(L"dooropen.wav");
				b_DoorSound2 = true;
			}

		}
	}
	else if (*(*iter)->GetRoomType() == 3)
	{
		if (g_iRoomMobCnt3 == 0)
		{
			for (int i = 0; i < 554; ++i)
			{
				++tileiter;
			}
			(*tileiter)->byDrawID = 13;
			(*tileiter)->byOption = 8;

			tileiter = CObjMgr::GetInst()->GetTile()->begin();
			for (int i = 0; i < 567; ++i)
			{
				++tileiter;
			}
			(*tileiter)->byDrawID = 15;
			(*tileiter)->byOption = 10;

			if (b_DoorSound3 == false)
			{
				CSoundMgr::GetInst()->EffectSound4(L"dooropen.wav");
				b_DoorSound3 = true;
			}

		}
	}
	else if (*(*iter)->GetRoomType() == 4)
	{
		if (g_iRoomMobCnt4 == 0)
		{
			for (int i = 0; i < 570; ++i)
			{
				++tileiter;
			}
			(*tileiter)->byDrawID = 13;
			(*tileiter)->byOption = 8;

			tileiter = CObjMgr::GetInst()->GetTile()->begin();
			for (int i = 0; i < 583; ++i)
			{
				++tileiter;
			}
			(*tileiter)->byDrawID = 21;
			(*tileiter)->byOption = 10;

			if (b_DoorSound4 == false)
			{
				CSoundMgr::GetInst()->EffectSound4(L"dooropen.wav");
				b_DoorSound4 = true;
			}

		}
	}
	else if (*(*iter)->GetRoomType() == 5)
	{
		if (g_iRoomMobCntBoss == 0)
		{
			for (int i = 0; i < 586; ++i)
			{
				++tileiter;
			}
			(*tileiter)->byDrawID = 23;
			(*tileiter)->byOption = 8;

			if (b_DoorSound5 == false)
			{
				CSoundMgr::GetInst()->EffectSound4(L"dooropen.wav");
				b_DoorSound5 = true;
			}
		}
	}*/
}


void CTileMgr::BombTile(void)
{
	//list<CObj*>::iterator iter = pObjList[OBJ_EFFECT_EXPLOSION].begin();
	//list<CObj*>::iterator iter_end = pObjList[OBJ_EFFECT_EXPLOSION].end();

	//for(iter; iter!=iter_end; iter++)
	//{
	//	if(pObjList[OBJ_EFFECT_EXPLOSION].size() <= 0)
	//		break;
	//	vector<TILE*>::const_iterator tileiter = CObjMgr::GetInst()->GetTile()->begin();
	//	vector<TILE*>::const_iterator tileiter_end = CObjMgr::GetInst()->GetTile()->end();

	//	for(tileiter; tileiter != tileiter_end; tileiter++)
	//	{
	//		float fWidth = (*iter)->GetInfo()->vSize.x/ 2.f + 50.f + (*tileiter)->vSize.x / 2.f;
	//		float fHeight = (*iter)->GetInfo()->vSize.y/ 2.f + 50.f + (*tileiter)->vSize.y / 2.f;

	//		float fDistX = fabs((*iter)->GetInfo()->vPos.x - (*tileiter)->vPos.x);
	//		float fDistY = fabs((*iter)->GetInfo()->vPos.y -(*tileiter)->vPos.y);

	//		if(pexplosionfx != NULL && pexplosionfy != NULL)
	//		{
	//			pexplosionfx = fWidth - fDistX;
	//			pexplosionfy = fHeight - fDistY;
	//		}

	//		if(fDistX < fWidth && fDistY < fHeight)
	//		{
	//			//0. ÀÌµ¿°¡´É 1. ÀÌµ¿ºÒ°¡ 2.°¡½Ã 3.X 4.µ¹ 
	//			//5.ºÒ 6.º® 7.´ÝÈù ¿Þ¹® 8.¿­¸° ¿Þ¹® 9.´ÝÈù ¿À¸¥¹® 
	//			//10.¿­¸° ¿À¸¥¹® 11. ´ÝÈù À­¹® 12.¿­¸° À­¹® 13.´ÝÈù ¾Æ·§¹® 14.¿­¸° ¾Æ·§¹®
	//			if(
	//				(*tileiter)->byOption == 1 ||
	//				(*tileiter)->byOption == 2 || 
	//				(*tileiter)->byOption == 6 ||
	//				(*tileiter)->byOption == 7 ||
	//				(*tileiter)->byOption == 9 ||
	//				(*tileiter)->byOption == 11||
	//				(*tileiter)->byOption == 13)
	//				break;

	//			if((*tileiter)->byOption == 4)
	//			{
	//				if(pexplosionfy > pexplosionfx)
	//				{
	//					//°¡·Î
	//					if((*iter)->GetInfo()->vPos.x  < (*tileiter)->vPos.x)
	//					{
	//						//¿ÞÂÊ
	//						(*tileiter)->byDrawID = 9;
	//						(*tileiter)->byOption = 0;
	//					}
	//					else
	//					{
	//						(*tileiter)->byDrawID = 9;
	//						(*tileiter)->byOption = 0;
	//					}
	//				}
	//				else
	//				{
	//					//¼¼·Î
	//					if((*iter)->GetInfo()->vPos.y  < (*tileiter)->vPos.y)
	//					{
	//						//À§
	//						(*tileiter)->byDrawID = 9;
	//						(*tileiter)->byOption = 0;
	//					}
	//					else
	//					{
	//						//¾Æ·¡
	//						(*tileiter)->byDrawID = 9;
	//						(*tileiter)->byOption = 0;
	//					}
	//				}

	//			}
	//			if((*tileiter)->byOption == 3)
	//			{
	//				if(pexplosionfy > pexplosionfx)
	//				{
	//					//°¡·Î
	//					if((*iter)->GetInfo()->vPos.x  < (*tileiter)->vPos.x)
	//					{
	//						//¿ÞÂÊ
	//						(*tileiter)->byDrawID = 5;
	//						(*tileiter)->byOption = 0;
	//						srand(unsigned(time(NULL)));
	//						(*tileiter)->byOption = 0;
	//						int rannum = rand()%10;
	//						if(rannum == 0)
	//							CObjMgr::GetInst()->AddObj(OBJ_ITEM_PICKUP, CObjFactory<CPickup>::CreateObj((*tileiter)->vPos,PICK_NICKEL));
	//						else if(rannum == 1)
	//							CObjMgr::GetInst()->AddObj(OBJ_ITEM_PICKUP, CObjFactory<CPickup>::CreateObj((*tileiter)->vPos,PICK_BOMB));
	//						else if(rannum == 2)
	//							CObjMgr::GetInst()->AddObj(OBJ_ITEM_PICKUP, CObjFactory<CPickup>::CreateObj((*tileiter)->vPos,PICK_DIME));
	//						else if(rannum == 3)
	//							CObjMgr::GetInst()->AddObj(OBJ_ITEM_PICKUP, CObjFactory<CPickup>::CreateObj((*tileiter)->vPos,PICK_DOUBLEBOMB));
	//						else if(rannum == 4)
	//							CObjMgr::GetInst()->AddObj(OBJ_ITEM_PICKUP, CObjFactory<CPickup>::CreateObj((*tileiter)->vPos,PICK_DOUBLEKEY));
	//						else if(rannum == 5)
	//							CObjMgr::GetInst()->AddObj(OBJ_ITEM_PICKUP, CObjFactory<CPickup>::CreateObj((*tileiter)->vPos,PICK_KEY));
	//						else if(rannum == 6)
	//							CObjMgr::GetInst()->AddObj(OBJ_ITEM_PICKUP, CObjFactory<CPickup>::CreateObj((*tileiter)->vPos,PICK_PENNY));
	//						else if(rannum == 7)
	//							CObjMgr::GetInst()->AddObj(OBJ_ITEM_PICKUP, CObjFactory<CPickup>::CreateObj((*tileiter)->vPos,PICK_HEART));
	//						else if(rannum == 8)
	//							CObjMgr::GetInst()->AddObj(OBJ_ITEM_PICKUP, CObjFactory<CPickup>::CreateObj((*tileiter)->vPos,PICK_HALFHEART));
	//						else if(rannum == 9)
	//							CObjMgr::GetInst()->AddObj(OBJ_ITEM_PICKUP, CObjFactory<CPickup>::CreateObj((*tileiter)->vPos,PICK_DOUBLEHEART));
	//					}
	//					else
	//					{
	//						(*tileiter)->byDrawID = 5;
	//						(*tileiter)->byOption = 0;
	//						srand(unsigned(time(NULL)));
	//						(*tileiter)->byOption = 0;
	//						int rannum = rand()%10;
	//						if(rannum == 0)
	//							CObjMgr::GetInst()->AddObj(OBJ_ITEM_PICKUP, CObjFactory<CPickup>::CreateObj((*tileiter)->vPos,PICK_NICKEL));
	//						else if(rannum == 1)
	//							CObjMgr::GetInst()->AddObj(OBJ_ITEM_PICKUP, CObjFactory<CPickup>::CreateObj((*tileiter)->vPos,PICK_BOMB));
	//						else if(rannum == 2)
	//							CObjMgr::GetInst()->AddObj(OBJ_ITEM_PICKUP, CObjFactory<CPickup>::CreateObj((*tileiter)->vPos,PICK_DIME));
	//						else if(rannum == 3)
	//							CObjMgr::GetInst()->AddObj(OBJ_ITEM_PICKUP, CObjFactory<CPickup>::CreateObj((*tileiter)->vPos,PICK_DOUBLEBOMB));
	//						else if(rannum == 4)
	//							CObjMgr::GetInst()->AddObj(OBJ_ITEM_PICKUP, CObjFactory<CPickup>::CreateObj((*tileiter)->vPos,PICK_DOUBLEKEY));
	//						else if(rannum == 5)
	//							CObjMgr::GetInst()->AddObj(OBJ_ITEM_PICKUP, CObjFactory<CPickup>::CreateObj((*tileiter)->vPos,PICK_KEY));
	//						else if(rannum == 6)
	//							CObjMgr::GetInst()->AddObj(OBJ_ITEM_PICKUP, CObjFactory<CPickup>::CreateObj((*tileiter)->vPos,PICK_PENNY));
	//						else if(rannum == 7)
	//							CObjMgr::GetInst()->AddObj(OBJ_ITEM_PICKUP, CObjFactory<CPickup>::CreateObj((*tileiter)->vPos,PICK_HEART));
	//						else if(rannum == 8)
	//							CObjMgr::GetInst()->AddObj(OBJ_ITEM_PICKUP, CObjFactory<CPickup>::CreateObj((*tileiter)->vPos,PICK_HALFHEART));
	//						else if(rannum == 9)
	//							CObjMgr::GetInst()->AddObj(OBJ_ITEM_PICKUP, CObjFactory<CPickup>::CreateObj((*tileiter)->vPos,PICK_DOUBLEHEART));
	//					}
	//				}
	//				else
	//				{
	//					//¼¼·Î
	//					if((*iter)->GetInfo()->vPos.y  < (*tileiter)->vPos.y)
	//					{
	//						//À§
	//						(*tileiter)->byDrawID = 5;
	//						(*tileiter)->byOption = 0;
	//						srand(unsigned(time(NULL)));
	//						(*tileiter)->byOption = 0;
	//						int rannum = rand()%10;
	//						if(rannum == 0)
	//							CObjMgr::GetInst()->AddObj(OBJ_ITEM_PICKUP, CObjFactory<CPickup>::CreateObj((*tileiter)->vPos,PICK_NICKEL));
	//						else if(rannum == 1)
	//							CObjMgr::GetInst()->AddObj(OBJ_ITEM_PICKUP, CObjFactory<CPickup>::CreateObj((*tileiter)->vPos,PICK_BOMB));
	//						else if(rannum == 2)
	//							CObjMgr::GetInst()->AddObj(OBJ_ITEM_PICKUP, CObjFactory<CPickup>::CreateObj((*tileiter)->vPos,PICK_DIME));
	//						else if(rannum == 3)
	//							CObjMgr::GetInst()->AddObj(OBJ_ITEM_PICKUP, CObjFactory<CPickup>::CreateObj((*tileiter)->vPos,PICK_DOUBLEBOMB));
	//						else if(rannum == 4)
	//							CObjMgr::GetInst()->AddObj(OBJ_ITEM_PICKUP, CObjFactory<CPickup>::CreateObj((*tileiter)->vPos,PICK_DOUBLEKEY));
	//						else if(rannum == 5)
	//							CObjMgr::GetInst()->AddObj(OBJ_ITEM_PICKUP, CObjFactory<CPickup>::CreateObj((*tileiter)->vPos,PICK_KEY));
	//						else if(rannum == 6)
	//							CObjMgr::GetInst()->AddObj(OBJ_ITEM_PICKUP, CObjFactory<CPickup>::CreateObj((*tileiter)->vPos,PICK_PENNY));
	//						else if(rannum == 7)
	//							CObjMgr::GetInst()->AddObj(OBJ_ITEM_PICKUP, CObjFactory<CPickup>::CreateObj((*tileiter)->vPos,PICK_HEART));
	//						else if(rannum == 8)
	//							CObjMgr::GetInst()->AddObj(OBJ_ITEM_PICKUP, CObjFactory<CPickup>::CreateObj((*tileiter)->vPos,PICK_HALFHEART));
	//						else if(rannum == 9)
	//							CObjMgr::GetInst()->AddObj(OBJ_ITEM_PICKUP, CObjFactory<CPickup>::CreateObj((*tileiter)->vPos,PICK_DOUBLEHEART));
	//					}
	//					else
	//					{
	//						//¾Æ·¡
	//						(*tileiter)->byDrawID = 5;
	//						(*tileiter)->byOption = 0;
	//						srand(unsigned(time(NULL)));
	//						(*tileiter)->byOption = 0;
	//						int rannum = rand()%10;
	//						if(rannum == 0)
	//							CObjMgr::GetInst()->AddObj(OBJ_ITEM_PICKUP, CObjFactory<CPickup>::CreateObj((*tileiter)->vPos,PICK_NICKEL));
	//						else if(rannum == 1)
	//							CObjMgr::GetInst()->AddObj(OBJ_ITEM_PICKUP, CObjFactory<CPickup>::CreateObj((*tileiter)->vPos,PICK_BOMB));
	//						else if(rannum == 2)
	//							CObjMgr::GetInst()->AddObj(OBJ_ITEM_PICKUP, CObjFactory<CPickup>::CreateObj((*tileiter)->vPos,PICK_DIME));
	//						else if(rannum == 3)
	//							CObjMgr::GetInst()->AddObj(OBJ_ITEM_PICKUP, CObjFactory<CPickup>::CreateObj((*tileiter)->vPos,PICK_DOUBLEBOMB));
	//						else if(rannum == 4)
	//							CObjMgr::GetInst()->AddObj(OBJ_ITEM_PICKUP, CObjFactory<CPickup>::CreateObj((*tileiter)->vPos,PICK_DOUBLEKEY));
	//						else if(rannum == 5)
	//							CObjMgr::GetInst()->AddObj(OBJ_ITEM_PICKUP, CObjFactory<CPickup>::CreateObj((*tileiter)->vPos,PICK_KEY));
	//						else if(rannum == 6)
	//							CObjMgr::GetInst()->AddObj(OBJ_ITEM_PICKUP, CObjFactory<CPickup>::CreateObj((*tileiter)->vPos,PICK_PENNY));
	//						else if(rannum == 7)
	//							CObjMgr::GetInst()->AddObj(OBJ_ITEM_PICKUP, CObjFactory<CPickup>::CreateObj((*tileiter)->vPos,PICK_HEART));
	//						else if(rannum == 8)
	//							CObjMgr::GetInst()->AddObj(OBJ_ITEM_PICKUP, CObjFactory<CPickup>::CreateObj((*tileiter)->vPos,PICK_HALFHEART));
	//						else if(rannum == 9)
	//							CObjMgr::GetInst()->AddObj(OBJ_ITEM_PICKUP, CObjFactory<CPickup>::CreateObj((*tileiter)->vPos,PICK_DOUBLEHEART));
	//					}
	//				}
	//			}
	//		}
	//	}
	//}
}
//0. ÀÌµ¿°¡´É 1. ÀÌµ¿ºÒ°¡ 2.°¡½Ã 3.X 4.µ¹ 
//5.ºÒ 6.º® 7.´ÝÈù ¿Þ¹® 8.¿­¸° ¿Þ¹® 9.´ÝÈù ¿À¸¥¹® 
//10.¿­¸° ¿À¸¥¹® 11. ´ÝÈù À­¹® 12.¿­¸° À­¹® 13.´ÝÈù ¾Æ·§¹® 14.¿­¸° ¾Æ·§¹®