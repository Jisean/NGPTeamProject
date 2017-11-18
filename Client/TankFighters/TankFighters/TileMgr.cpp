#include "StdAfx.h"
#include "TileMgr.h"
#include "ObjMgr.h"
#include "BackGround.h"
#include "KeyMgr_Song.h"
#include "ObjFactory.h"
#include "Pickup.h"
#include <time.h>
#include "SoundMgr.h"
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
	BulletTile();
	DoorTile();
	BombTile();
}
void CTileMgr::PlayerTile(void)
{
	list<CObj*>::iterator iter = pObjList[OBJ_PLAYER].begin();

	vector<TILE*>::const_iterator tileiter = CObjMgr::GetInst()->GetTile()->begin();
	vector<TILE*>::const_iterator tileiter_end = CObjMgr::GetInst()->GetTile()->end();

	for(tileiter; tileiter != tileiter_end; tileiter++)
	{

		float fWidth = (*iter)->GetInfo()->vSize.x - 3 / 2.f + (*tileiter)->vSize.x / 2.f;
		float fHeight = (*iter)->GetInfo()->vSize.y / 2.f + (*tileiter)->vSize.y / 2.f;

		float fDistX = fabs((*iter)->GetInfo()->vPos.x - (*tileiter)->vPos.x);
		float fDistY = fabs((*iter)->GetInfo()->vPos.y -(*tileiter)->vPos.y);

		if(pfx != NULL && pfy != NULL)
		{
			pfx = fWidth - fDistX;
			pfy = fHeight - fDistY;
		}

		if(fDistX < fWidth && fDistY < fHeight)
		{
			//0. �̵����� 1. �̵��Ұ� 2.���� 3.X 4.�� 
			//5.�� 6.�� 7.���� �޹� 8.���� �޹� 9.���� ������ 
			//10.���� ������ 11. ���� ���� 12.���� ���� 13.���� �Ʒ��� 14.���� �Ʒ���
			if((*tileiter)->byOption == 1 || 
				(*tileiter)->byOption == 3 ||
				(*tileiter)->byOption == 4 ||
				(*tileiter)->byOption == 6 || 
				(*tileiter)->byOption == 7 ||
				(*tileiter)->byOption == 9 ||
				(*tileiter)->byOption == 11 ||
				(*tileiter)->byOption == 13)
			{
				if(pfy > pfx)
				{
					//����
					if((*iter)->GetInfo()->vPos.x  < (*tileiter)->vPos.x)
					{
						//����
						//if(KeyMgr_Song::GetInstance()->GetKeyState('D'))
						(*iter)->GetInfo()->vPos.x -= (*iter)->GetSpeed();
					}
					else
					{
						//������
						//if(KeyMgr_Song::GetInstance()->GetKeyState('A'))
						(*iter)->GetInfo()->vPos.x +=(*iter)->GetSpeed();
					}
				}
				else
				{
					//����
					if((*iter)->GetInfo()->vPos.y  < (*tileiter)->vPos.y)
					{
						//��
						//if(KeyMgr_Song::GetInstance()->GetKeyState('S'))
						(*iter)->GetInfo()->vPos.y -= (*iter)->GetSpeed();
					}
					else
					{
						//�Ʒ�
						//if(KeyMgr_Song::GetInstance()->GetKeyState('W'))
						(*iter)->GetInfo()->vPos.y +=(*iter)->GetSpeed();
					}
				}
			}
			if((*tileiter)->byOption == 2 && *(*iter)->GetInvincible() == false)
			{
				srand((unsigned)time(NULL));
				if(pfy > pfx)
				{
					//����
					if((*iter)->GetInfo()->vPos.x  < (*tileiter)->vPos.x)
					{
						//����

						if(rand()%2 ==0)
							CSoundMgr::GetInst()->EffectSound1(L"playerhit1.wav");
						else
							CSoundMgr::GetInst()->EffectSound1(L"playerhit2.wav");
						(*iter)->SetHP(-0.5f);
						(*iter)->SetInvincible();

					}
					else
					{
						//������

						if(rand()%2 ==0)
							CSoundMgr::GetInst()->EffectSound1(L"playerhit1.wav");
						else
							CSoundMgr::GetInst()->EffectSound1(L"playerhit2.wav");
						(*iter)->SetHP(-0.5f);
						(*iter)->SetInvincible();

					}
				}
				else
				{
					//����
					if((*iter)->GetInfo()->vPos.y  < (*tileiter)->vPos.y)
					{
						//��

						if(rand()%2 ==0)
							CSoundMgr::GetInst()->EffectSound1(L"playerhit1.wav");
						else
							CSoundMgr::GetInst()->EffectSound1(L"playerhit2.wav");
						(*iter)->SetHP(-0.5f);
						(*iter)->SetInvincible();

					}
					else
					{
						//�Ʒ�

						if(rand()%2 ==0)
							CSoundMgr::GetInst()->EffectSound1(L"playerhit1.wav");
						else
							CSoundMgr::GetInst()->EffectSound1(L"playerhit2.wav");
						(*iter)->SetHP(-0.5f);
						(*iter)->SetInvincible();
					}
				}
			}
			if((*tileiter)->byOption == 8)
			{
				if(pfy > pfx)
				{
					//����
					if((*iter)->GetInfo()->vPos.x  < (*tileiter)->vPos.x)
					{
						//����
						//if(KeyMgr_Song::GetInstance()->GetKeyState('D'))
						for(int i = 0 ; i < 4; ++i)
						{
							--tileiter;
						}
						(*iter)->GetInfo()->vPos = (*tileiter)->vPos;
						(*iter)->SetRoomTypeLeft();
					}
					else
					{
						//������
						//if(KeyMgr_Song::GetInstance()->GetKeyState('A'))
						for(int i = 0 ; i < 4; ++i)
						{
							--tileiter;
						}
						(*iter)->GetInfo()->vPos = (*tileiter)->vPos;
						(*iter)->SetRoomTypeLeft();
					}
				}
				else
				{
					//����
					if((*iter)->GetInfo()->vPos.y  < (*tileiter)->vPos.y)
					{
						//��
						//if(KeyMgr_Song::GetInstance()->GetKeyState('S'))
						for(int i = 0 ; i < 4; ++i)
						{
							--tileiter;
						}
						(*iter)->GetInfo()->vPos = (*tileiter)->vPos;
						(*iter)->SetRoomTypeLeft();
					}
					else
					{
						//�Ʒ�
						//if(KeyMgr_Song::GetInstance()->GetKeyState('W'))
						for(int i = 0 ; i < 4; ++i)
						{
							--tileiter;
						}
						(*iter)->GetInfo()->vPos = (*tileiter)->vPos;
						(*iter)->SetRoomTypeLeft();
					}
				}
			}
			if((*tileiter)->byOption == 10)
			{
				if(pfy > pfx)
				{
					//����
					if((*iter)->GetInfo()->vPos.x  < (*tileiter)->vPos.x)
					{
						//����
						//if(KeyMgr_Song::GetInstance()->GetKeyState('D'))
						for(int i = 0 ; i < 4; ++i)
						{
							++tileiter;
						}
						(*iter)->GetInfo()->vPos = (*tileiter)->vPos;
						(*iter)->SetRoomTypeRight();
					}
					else
					{
						//������
						//if(KeyMgr_Song::GetInstance()->GetKeyState('A'))
						for(int i = 0 ; i < 4; ++i)
						{
							++tileiter;
						}
						(*iter)->GetInfo()->vPos = (*tileiter)->vPos;
						(*iter)->SetRoomTypeRight();
					}
				}
				else
				{
					//����
					if((*iter)->GetInfo()->vPos.y  < (*tileiter)->vPos.y)
					{
						//��
						//if(KeyMgr_Song::GetInstance()->GetKeyState('S'))
						for(int i = 0 ; i < 4; ++i)
						{
							++tileiter;
						}
						(*iter)->GetInfo()->vPos = (*tileiter)->vPos;
						(*iter)->SetRoomTypeRight();
					}
					else
					{
						//�Ʒ�
						//if(KeyMgr_Song::GetInstance()->GetKeyState('W'))
						for(int i = 0 ; i < 4; ++i)
						{
							++tileiter;
						}
						(*iter)->GetInfo()->vPos = (*tileiter)->vPos;
						(*iter)->SetRoomTypeRight();
					}
				}
			}
			if((*tileiter)->byOption == 12)
			{
				if(pfy > pfx)
				{
					//����
					if((*iter)->GetInfo()->vPos.x  < (*tileiter)->vPos.x)
					{
						//����
						//if(KeyMgr_Song::GetInstance()->GetKeyState('D'))
						for(int i = 0 ; i < 404; ++i)
						{
							--tileiter;
						}
						(*iter)->GetInfo()->vPos = (*tileiter)->vPos;
						(*iter)->SetRoomTypeUp();
					}
					else
					{
						//������
						//if(KeyMgr_Song::GetInstance()->GetKeyState('A'))
						for(int i = 0 ; i < 404; ++i)
						{
							--tileiter;
						}
						(*iter)->GetInfo()->vPos = (*tileiter)->vPos;
						(*iter)->SetRoomTypeUp();
					}
				}
				else
				{
					//����
					if((*iter)->GetInfo()->vPos.y  < (*tileiter)->vPos.y)
					{
						//��
						//if(KeyMgr_Song::GetInstance()->GetKeyState('S'))
						for(int i = 0 ; i < 404; ++i)
						{
							--tileiter;
						}
						(*iter)->GetInfo()->vPos = (*tileiter)->vPos;
						(*iter)->SetRoomTypeUp();
					}
					else
					{
						//�Ʒ�
						//if(KeyMgr_Song::GetInstance()->GetKeyState('W'))
						for(int i = 0 ; i < 404; ++i)
						{
							--tileiter;
						}
						(*iter)->GetInfo()->vPos = (*tileiter)->vPos;
						(*iter)->SetRoomTypeUp();
					}
				}
			}
			if((*tileiter)->byOption == 14)
			{
				if(pfy > pfx)
				{
					//����
					if((*iter)->GetInfo()->vPos.x  < (*tileiter)->vPos.x)
					{
						//����
						//if(KeyMgr_Song::GetInstance()->GetKeyState('D'))
						for(int i = 0 ; i < 404; ++i)
						{
							++tileiter;
						}
						(*iter)->GetInfo()->vPos = (*tileiter)->vPos;
						(*iter)->SetRoomTypeDown();
					}
					else
					{
						//������
						//if(KeyMgr_Song::GetInstance()->GetKeyState('A'))
						for(int i = 0 ; i < 404; ++i)
						{
							++tileiter;
						}
						(*iter)->GetInfo()->vPos = (*tileiter)->vPos;
						(*iter)->SetRoomTypeDown();
					}
				}
				else
				{
					//����
					if((*iter)->GetInfo()->vPos.y  < (*tileiter)->vPos.y)
					{
						//��
						//if(KeyMgr_Song::GetInstance()->GetKeyState('S'))
						for(int i = 0 ; i < 404; ++i)
						{
							++tileiter;
						}
						(*iter)->GetInfo()->vPos = (*tileiter)->vPos;
						(*iter)->SetRoomTypeDown();
					}
					else
					{
						//�Ʒ�
						//if(KeyMgr_Song::GetInstance()->GetKeyState('W'))
						for(int i = 0 ; i < 404; ++i)
						{
							++tileiter;
						}
						(*iter)->GetInfo()->vPos = (*tileiter)->vPos;
						(*iter)->SetRoomTypeDown();
					}
				}
			}
		}
	}

}

void CTileMgr::TearTile(void)
{
	list<CObj*>::iterator iter = pObjList[OBJ_TEAR].begin();
	list<CObj*>::iterator iter_end = pObjList[OBJ_TEAR].end();

	for(iter; iter!=iter_end; iter++)
	{
		if(pObjList[OBJ_TEAR].size() <= 0)
			return;
		vector<TILE*>::const_iterator tileiter = CObjMgr::GetInst()->GetTile()->begin();
		vector<TILE*>::const_iterator tileiter_end = CObjMgr::GetInst()->GetTile()->end();

		for(tileiter; tileiter != tileiter_end; tileiter++)
		{
			float fWidth = (*iter)->GetInfo()->vSize.x / 2.f + (*tileiter)->vSize.x / 2.f;
			float fHeight = (*iter)->GetInfo()->vSize.y / 2.f + (*tileiter)->vSize.y / 2.f;

			float fDistX = fabs((*iter)->GetInfo()->vPos.x - (*tileiter)->vPos.x);
			float fDistY = fabs((*iter)->GetInfo()->vPos.y -(*tileiter)->vPos.y);

			if(ptearfx != NULL && ptearfy != NULL)
			{
				ptearfx = fWidth - fDistX;
				ptearfy = fHeight - fDistY;
			}

			if(fDistX < fWidth && fDistY < fHeight)
			{
				if((*tileiter)->byOption == 0)
					return;

				if((*tileiter)->byOption == 1 || 
					(*tileiter)->byOption == 3 ||
					(*tileiter)->byOption == 4 || 
					(*tileiter)->byOption == 7 ||
					(*tileiter)->byOption == 9 ||
					(*tileiter)->byOption == 11 ||
					(*tileiter)->byOption == 13)
				{
					if(ptearfy > ptearfx)
					{
						//����
						if((*iter)->GetInfo()->vPos.x  < (*tileiter)->vPos.x)
						{
							//����
							(*iter)->SetDead();
						}
						else
						{
							(*iter)->SetDead();
						}
					}
					else
					{
						//����
						if((*iter)->GetInfo()->vPos.y  < (*tileiter)->vPos.y)
						{
							//��
							(*iter)->SetDead();
						}
						else
						{
							//�Ʒ�
							(*iter)->SetDead();
						}
					}

				}
				if((*tileiter)->byOption == 3)
				{
					if(ptearfy > ptearfx)
					{
						//����
						if((*iter)->GetInfo()->vPos.x  < (*tileiter)->vPos.x)
						{
							//����
							(*iter)->SetDead();
							++(*tileiter)->byDrawID;
						}
						else
						{
							(*iter)->SetDead();
							++(*tileiter)->byDrawID;
						}
					}
					else
					{
						//����
						if((*iter)->GetInfo()->vPos.y  < (*tileiter)->vPos.y)
						{
							//��
							(*iter)->SetDead();
							++(*tileiter)->byDrawID;
						}
						else
						{
							//�Ʒ�
							(*iter)->SetDead();
							++(*tileiter)->byDrawID;
						}
					}
					if((*tileiter)->byDrawID == 5)
					{
						srand(unsigned(time(NULL)));
						(*tileiter)->byOption = 0;
						int rannum = rand()%10;
						if(rannum == 0)
							CObjMgr::GetInst()->AddObj(OBJ_ITEM_PICKUP, CObjFactory<CPickup>::CreateObj((*tileiter)->vPos,PICK_NICKEL));
						else if(rannum == 1)
							CObjMgr::GetInst()->AddObj(OBJ_ITEM_PICKUP, CObjFactory<CPickup>::CreateObj((*tileiter)->vPos,PICK_BOMB));
						else if(rannum == 2)
							CObjMgr::GetInst()->AddObj(OBJ_ITEM_PICKUP, CObjFactory<CPickup>::CreateObj((*tileiter)->vPos,PICK_DIME));
						else if(rannum == 3)
							CObjMgr::GetInst()->AddObj(OBJ_ITEM_PICKUP, CObjFactory<CPickup>::CreateObj((*tileiter)->vPos,PICK_DOUBLEBOMB));
						else if(rannum == 4)
							CObjMgr::GetInst()->AddObj(OBJ_ITEM_PICKUP, CObjFactory<CPickup>::CreateObj((*tileiter)->vPos,PICK_DOUBLEKEY));
						else if(rannum == 5)
							CObjMgr::GetInst()->AddObj(OBJ_ITEM_PICKUP, CObjFactory<CPickup>::CreateObj((*tileiter)->vPos,PICK_KEY));
						else if(rannum == 6)
							CObjMgr::GetInst()->AddObj(OBJ_ITEM_PICKUP, CObjFactory<CPickup>::CreateObj((*tileiter)->vPos,PICK_PENNY));
						else if(rannum == 7)
							CObjMgr::GetInst()->AddObj(OBJ_ITEM_PICKUP, CObjFactory<CPickup>::CreateObj((*tileiter)->vPos,PICK_HEART));
						else if(rannum == 8)
							CObjMgr::GetInst()->AddObj(OBJ_ITEM_PICKUP, CObjFactory<CPickup>::CreateObj((*tileiter)->vPos,PICK_HALFHEART));
						else if(rannum == 9)
							CObjMgr::GetInst()->AddObj(OBJ_ITEM_PICKUP, CObjFactory<CPickup>::CreateObj((*tileiter)->vPos,PICK_DOUBLEHEART));
					}
				}
			}
		}
	}
}
void CTileMgr::MonsterTile(void)
{
	list<CObj*>::iterator iter = pObjList[OBJ_MONSTER].begin();
	list<CObj*>::iterator iter_end = pObjList[OBJ_MONSTER].end();

	vector<TILE*>::const_iterator tileiter = CObjMgr::GetInst()->GetTile()->begin();
	vector<TILE*>::const_iterator tileiter_end = CObjMgr::GetInst()->GetTile()->end();

	for(iter; iter != iter_end; ++iter)
	{
		for(tileiter; tileiter != tileiter_end; ++tileiter)
		{

			float fWidth = (*iter)->GetInfo()->vSize.x - 3 / 2.f + (*tileiter)->vSize.x / 2.f;
			float fHeight = (*iter)->GetInfo()->vSize.y / 2.f + (*tileiter)->vSize.y / 2.f;

			float fDistX = fabs((*iter)->GetInfo()->vPos.x - (*tileiter)->vPos.x);
			float fDistY = fabs((*iter)->GetInfo()->vPos.y -(*tileiter)->vPos.y);

			if(pmonsterfx != NULL && pmonsterfy != NULL)
			{
				pmonsterfx = fWidth - fDistX;
				pmonsterfy = fHeight - fDistY;
			}

			if(fDistX < fWidth && fDistY < fHeight)
			{
				//0. �̵����� 1. �̵��Ұ� 2.���� 3.X 4.�� 
				//5.�� 6.�� 7.���� �޹� 8.���� �޹� 9.���� ������ 
				//10.���� ������ 11. ���� ���� 12.���� ���� 13.���� �Ʒ��� 14.���� �Ʒ���
				if((*tileiter)->byOption == 0)
				{
					(*tileiter)->byOption = 1;
				}
				if( (*tileiter)->byOption == 3 ||
					(*tileiter)->byOption == 4 ||
					(*tileiter)->byOption == 6 || 
					(*tileiter)->byOption == 7 ||
					(*tileiter)->byOption == 9 ||
					(*tileiter)->byOption == 11 ||
					(*tileiter)->byOption == 13)
				{
					if(pmonsterfy > pmonsterfx)
					{
						//����
						if((*iter)->GetInfo()->vPos.x  < (*tileiter)->vPos.x)
						{
							//����
							//if(KeyMgr_Song::GetInstance()->GetKeyState('D'))
							(*iter)->GetInfo()->vPos.x -= (*iter)->GetInfo()->vDir.x;;
						}
						else
						{
							//������
							//if(KeyMgr_Song::GetInstance()->GetKeyState('A'))
							(*iter)->GetInfo()->vPos.x +=(*iter)->GetInfo()->vDir.x;;
						}
					}
					else
					{
						//����
						if((*iter)->GetInfo()->vPos.y  < (*tileiter)->vPos.y)
						{
							//��
							//if(KeyMgr_Song::GetInstance()->GetKeyState('S'))
							(*iter)->GetInfo()->vPos.y -= (*iter)->GetInfo()->vDir.y;;
						}
						else
						{
							//�Ʒ�
							//if(KeyMgr_Song::GetInstance()->GetKeyState('W'))
							(*iter)->GetInfo()->vPos.y +=(*iter)->GetInfo()->vDir.y;;
						}
					}
				}
				else
				{
					if((*tileiter)->byOption == 1)
					{
						(*tileiter)->byOption = 0;
					}
				}
			}
		}
	}
}

void CTileMgr::BulletTile(void)
{
	list<CObj*>::iterator iter = pObjList[OBJ_BULLET].begin();
	list<CObj*>::iterator iter_end = pObjList[OBJ_BULLET].end();

	for(iter; iter!=iter_end; iter++)
	{
		if(pObjList[OBJ_BULLET].size() <= 0)
			return;
		vector<TILE*>::const_iterator tileiter = CObjMgr::GetInst()->GetTile()->begin();
		vector<TILE*>::const_iterator tileiter_end = CObjMgr::GetInst()->GetTile()->end();

		for(tileiter; tileiter != tileiter_end; tileiter++)
		{
			float fWidth = (*iter)->GetInfo()->vSize.x / 2.f + (*tileiter)->vSize.x / 2.f;
			float fHeight = (*iter)->GetInfo()->vSize.y / 2.f + (*tileiter)->vSize.y / 2.f;

			float fDistX = fabs((*iter)->GetInfo()->vPos.x - (*tileiter)->vPos.x);
			float fDistY = fabs((*iter)->GetInfo()->vPos.y -(*tileiter)->vPos.y);

			if(pbulletfx != NULL && pbulletfy != NULL)
			{
				pbulletfx = fWidth - fDistX;
				pbulletfy = fHeight - fDistY;
			}

			if(fDistX < fWidth && fDistY < fHeight)
			{
				if((*tileiter)->byOption == 0)
					return;

				//0. �̵����� 1. �̵��Ұ� 2.���� 3.X 4.�� 
				//5.�� 6.�� 7.���� �޹� 8.���� �޹� 9.���� ������ 
				//10.���� ������ 11. ���� ���� 12.���� ���� 13.���� �Ʒ��� 14.���� �Ʒ���
				if((*tileiter)->byOption == 1 || 
					(*tileiter)->byOption == 3 ||
					(*tileiter)->byOption == 4 ||
					(*tileiter)->byOption == 5 || 
					(*tileiter)->byOption == 7 ||
					(*tileiter)->byOption == 8 ||
					(*tileiter)->byOption == 9 ||
					(*tileiter)->byOption == 10 ||
					(*tileiter)->byOption == 11 ||
					(*tileiter)->byOption == 12 ||
					(*tileiter)->byOption == 13 ||
					(*tileiter)->byOption == 14)
				{
					if(pbulletfy > pbulletfx)
					{
						//����
						if((*iter)->GetInfo()->vPos.x  < (*tileiter)->vPos.x)
						{
							//����
							(*iter)->SetDead();
						}
						else
						{
							(*iter)->SetDead();
						}
					}
					else
					{
						//����
						if((*iter)->GetInfo()->vPos.y  < (*tileiter)->vPos.y)
						{
							//��
							(*iter)->SetDead();
						}
						else
						{
							//�Ʒ�
							(*iter)->SetDead();
						}
					}

				}
			}
		}
	}
}
void CTileMgr::DoorTile(void)
{
	list<CObj*>::iterator iter = pObjList[OBJ_PLAYER].begin();
	vector<TILE*>::const_iterator tileiter = CObjMgr::GetInst()->GetTile()->begin();
	vector<TILE*>::const_iterator tileiter_end = CObjMgr::GetInst()->GetTile()->end();

	if(*(*iter)->GetRoomType() == 1)
	{
		if(g_iRoomMobCnt1 == 0)
		{
			for(int i = 0 ; i < 522; ++i)
			{
				++tileiter;
			}
			(*tileiter)->byDrawID = 13;
			(*tileiter)->byOption = 8;

			tileiter = CObjMgr::GetInst()->GetTile()->begin();
			for(int i = 0; i < 535; ++i)
			{
				++tileiter;
			}
			(*tileiter)->byDrawID = 15;
			(*tileiter)->byOption = 10;

			if(b_DoorSound1 == false)
			{
				CSoundMgr::GetInst()->EffectSound4(L"dooropen.wav");
				b_DoorSound1 = true;
			}

		}
	}
	else if(*(*iter)->GetRoomType() == 2)
	{
		if(g_iRoomMobCnt2 == -4)
		{
			for(int i = 0 ; i < 538; ++i)
			{
				++tileiter;
			}
			(*tileiter)->byDrawID = 13;
			(*tileiter)->byOption = 8;

			tileiter = CObjMgr::GetInst()->GetTile()->begin();
			for(int i = 0; i < 551; ++i)
			{
				++tileiter;
			}
			(*tileiter)->byDrawID = 15;
			(*tileiter)->byOption = 10;

			tileiter = CObjMgr::GetInst()->GetTile()->begin();
			for(int i = 0; i < 948; ++i)
			{
				++tileiter;
			}
			(*tileiter)->byDrawID = 11;
			(*tileiter)->byOption = 14;

			if(b_DoorSound2 == false)
			{
				CSoundMgr::GetInst()->EffectSound4(L"dooropen.wav");
				b_DoorSound2 = true;
			}

		}
	}
	else if(*(*iter)->GetRoomType() == 3)
	{
		if(g_iRoomMobCnt3 == 0)
		{
			for(int i = 0 ; i < 554; ++i)
			{
				++tileiter;
			}
			(*tileiter)->byDrawID = 13;
			(*tileiter)->byOption = 8;

			tileiter = CObjMgr::GetInst()->GetTile()->begin();
			for(int i = 0; i < 567; ++i)
			{
				++tileiter;
			}
			(*tileiter)->byDrawID = 15;
			(*tileiter)->byOption = 10;

			if(b_DoorSound3 == false)
			{
				CSoundMgr::GetInst()->EffectSound4(L"dooropen.wav");
				b_DoorSound3 = true;
			}

		}
	}
	else if(*(*iter)->GetRoomType() == 4)
	{
		if(g_iRoomMobCnt4 == 0)
		{
			for(int i = 0 ; i < 570; ++i)
			{
				++tileiter;
			}
			(*tileiter)->byDrawID = 13;
			(*tileiter)->byOption = 8;

			tileiter = CObjMgr::GetInst()->GetTile()->begin();
			for(int i = 0; i < 583; ++i)
			{
				++tileiter;
			}
			(*tileiter)->byDrawID = 21;
			(*tileiter)->byOption = 10;

			if(b_DoorSound4 == false)
			{
				CSoundMgr::GetInst()->EffectSound4(L"dooropen.wav");
				b_DoorSound4 = true;
			}

		}
	}
	else if(*(*iter)->GetRoomType() == 5)
	{
		if(g_iRoomMobCntBoss == 0)
		{
			for(int i = 0 ; i < 586; ++i)
			{
				++tileiter;
			}
			(*tileiter)->byDrawID = 23;
			(*tileiter)->byOption = 8;

			if(b_DoorSound5 == false)
			{
				CSoundMgr::GetInst()->EffectSound4(L"dooropen.wav");
				b_DoorSound5 = true;
			}
		}
	}
}


void CTileMgr::BombTile(void)
{
	list<CObj*>::iterator iter = pObjList[OBJ_EFFECT_EXPLOSION].begin();
	list<CObj*>::iterator iter_end = pObjList[OBJ_EFFECT_EXPLOSION].end();

	for(iter; iter!=iter_end; iter++)
	{
		if(pObjList[OBJ_EFFECT_EXPLOSION].size() <= 0)
			break;
		vector<TILE*>::const_iterator tileiter = CObjMgr::GetInst()->GetTile()->begin();
		vector<TILE*>::const_iterator tileiter_end = CObjMgr::GetInst()->GetTile()->end();

		for(tileiter; tileiter != tileiter_end; tileiter++)
		{
			float fWidth = (*iter)->GetInfo()->vSize.x/ 2.f + 50.f + (*tileiter)->vSize.x / 2.f;
			float fHeight = (*iter)->GetInfo()->vSize.y/ 2.f + 50.f + (*tileiter)->vSize.y / 2.f;

			float fDistX = fabs((*iter)->GetInfo()->vPos.x - (*tileiter)->vPos.x);
			float fDistY = fabs((*iter)->GetInfo()->vPos.y -(*tileiter)->vPos.y);

			if(pexplosionfx != NULL && pexplosionfy != NULL)
			{
				pexplosionfx = fWidth - fDistX;
				pexplosionfy = fHeight - fDistY;
			}

			if(fDistX < fWidth && fDistY < fHeight)
			{
				//0. �̵����� 1. �̵��Ұ� 2.���� 3.X 4.�� 
				//5.�� 6.�� 7.���� �޹� 8.���� �޹� 9.���� ������ 
				//10.���� ������ 11. ���� ���� 12.���� ���� 13.���� �Ʒ��� 14.���� �Ʒ���
				if(
					(*tileiter)->byOption == 1 ||
					(*tileiter)->byOption == 2 || 
					(*tileiter)->byOption == 6 ||
					(*tileiter)->byOption == 7 ||
					(*tileiter)->byOption == 9 ||
					(*tileiter)->byOption == 11||
					(*tileiter)->byOption == 13)
					break;

				if((*tileiter)->byOption == 4)
				{
					if(pexplosionfy > pexplosionfx)
					{
						//����
						if((*iter)->GetInfo()->vPos.x  < (*tileiter)->vPos.x)
						{
							//����
							(*tileiter)->byDrawID = 9;
							(*tileiter)->byOption = 0;
						}
						else
						{
							(*tileiter)->byDrawID = 9;
							(*tileiter)->byOption = 0;
						}
					}
					else
					{
						//����
						if((*iter)->GetInfo()->vPos.y  < (*tileiter)->vPos.y)
						{
							//��
							(*tileiter)->byDrawID = 9;
							(*tileiter)->byOption = 0;
						}
						else
						{
							//�Ʒ�
							(*tileiter)->byDrawID = 9;
							(*tileiter)->byOption = 0;
						}
					}

				}
				if((*tileiter)->byOption == 3)
				{
					if(pexplosionfy > pexplosionfx)
					{
						//����
						if((*iter)->GetInfo()->vPos.x  < (*tileiter)->vPos.x)
						{
							//����
							(*tileiter)->byDrawID = 5;
							(*tileiter)->byOption = 0;
							srand(unsigned(time(NULL)));
							(*tileiter)->byOption = 0;
							int rannum = rand()%10;
							if(rannum == 0)
								CObjMgr::GetInst()->AddObj(OBJ_ITEM_PICKUP, CObjFactory<CPickup>::CreateObj((*tileiter)->vPos,PICK_NICKEL));
							else if(rannum == 1)
								CObjMgr::GetInst()->AddObj(OBJ_ITEM_PICKUP, CObjFactory<CPickup>::CreateObj((*tileiter)->vPos,PICK_BOMB));
							else if(rannum == 2)
								CObjMgr::GetInst()->AddObj(OBJ_ITEM_PICKUP, CObjFactory<CPickup>::CreateObj((*tileiter)->vPos,PICK_DIME));
							else if(rannum == 3)
								CObjMgr::GetInst()->AddObj(OBJ_ITEM_PICKUP, CObjFactory<CPickup>::CreateObj((*tileiter)->vPos,PICK_DOUBLEBOMB));
							else if(rannum == 4)
								CObjMgr::GetInst()->AddObj(OBJ_ITEM_PICKUP, CObjFactory<CPickup>::CreateObj((*tileiter)->vPos,PICK_DOUBLEKEY));
							else if(rannum == 5)
								CObjMgr::GetInst()->AddObj(OBJ_ITEM_PICKUP, CObjFactory<CPickup>::CreateObj((*tileiter)->vPos,PICK_KEY));
							else if(rannum == 6)
								CObjMgr::GetInst()->AddObj(OBJ_ITEM_PICKUP, CObjFactory<CPickup>::CreateObj((*tileiter)->vPos,PICK_PENNY));
							else if(rannum == 7)
								CObjMgr::GetInst()->AddObj(OBJ_ITEM_PICKUP, CObjFactory<CPickup>::CreateObj((*tileiter)->vPos,PICK_HEART));
							else if(rannum == 8)
								CObjMgr::GetInst()->AddObj(OBJ_ITEM_PICKUP, CObjFactory<CPickup>::CreateObj((*tileiter)->vPos,PICK_HALFHEART));
							else if(rannum == 9)
								CObjMgr::GetInst()->AddObj(OBJ_ITEM_PICKUP, CObjFactory<CPickup>::CreateObj((*tileiter)->vPos,PICK_DOUBLEHEART));
						}
						else
						{
							(*tileiter)->byDrawID = 5;
							(*tileiter)->byOption = 0;
							srand(unsigned(time(NULL)));
							(*tileiter)->byOption = 0;
							int rannum = rand()%10;
							if(rannum == 0)
								CObjMgr::GetInst()->AddObj(OBJ_ITEM_PICKUP, CObjFactory<CPickup>::CreateObj((*tileiter)->vPos,PICK_NICKEL));
							else if(rannum == 1)
								CObjMgr::GetInst()->AddObj(OBJ_ITEM_PICKUP, CObjFactory<CPickup>::CreateObj((*tileiter)->vPos,PICK_BOMB));
							else if(rannum == 2)
								CObjMgr::GetInst()->AddObj(OBJ_ITEM_PICKUP, CObjFactory<CPickup>::CreateObj((*tileiter)->vPos,PICK_DIME));
							else if(rannum == 3)
								CObjMgr::GetInst()->AddObj(OBJ_ITEM_PICKUP, CObjFactory<CPickup>::CreateObj((*tileiter)->vPos,PICK_DOUBLEBOMB));
							else if(rannum == 4)
								CObjMgr::GetInst()->AddObj(OBJ_ITEM_PICKUP, CObjFactory<CPickup>::CreateObj((*tileiter)->vPos,PICK_DOUBLEKEY));
							else if(rannum == 5)
								CObjMgr::GetInst()->AddObj(OBJ_ITEM_PICKUP, CObjFactory<CPickup>::CreateObj((*tileiter)->vPos,PICK_KEY));
							else if(rannum == 6)
								CObjMgr::GetInst()->AddObj(OBJ_ITEM_PICKUP, CObjFactory<CPickup>::CreateObj((*tileiter)->vPos,PICK_PENNY));
							else if(rannum == 7)
								CObjMgr::GetInst()->AddObj(OBJ_ITEM_PICKUP, CObjFactory<CPickup>::CreateObj((*tileiter)->vPos,PICK_HEART));
							else if(rannum == 8)
								CObjMgr::GetInst()->AddObj(OBJ_ITEM_PICKUP, CObjFactory<CPickup>::CreateObj((*tileiter)->vPos,PICK_HALFHEART));
							else if(rannum == 9)
								CObjMgr::GetInst()->AddObj(OBJ_ITEM_PICKUP, CObjFactory<CPickup>::CreateObj((*tileiter)->vPos,PICK_DOUBLEHEART));
						}
					}
					else
					{
						//����
						if((*iter)->GetInfo()->vPos.y  < (*tileiter)->vPos.y)
						{
							//��
							(*tileiter)->byDrawID = 5;
							(*tileiter)->byOption = 0;
							srand(unsigned(time(NULL)));
							(*tileiter)->byOption = 0;
							int rannum = rand()%10;
							if(rannum == 0)
								CObjMgr::GetInst()->AddObj(OBJ_ITEM_PICKUP, CObjFactory<CPickup>::CreateObj((*tileiter)->vPos,PICK_NICKEL));
							else if(rannum == 1)
								CObjMgr::GetInst()->AddObj(OBJ_ITEM_PICKUP, CObjFactory<CPickup>::CreateObj((*tileiter)->vPos,PICK_BOMB));
							else if(rannum == 2)
								CObjMgr::GetInst()->AddObj(OBJ_ITEM_PICKUP, CObjFactory<CPickup>::CreateObj((*tileiter)->vPos,PICK_DIME));
							else if(rannum == 3)
								CObjMgr::GetInst()->AddObj(OBJ_ITEM_PICKUP, CObjFactory<CPickup>::CreateObj((*tileiter)->vPos,PICK_DOUBLEBOMB));
							else if(rannum == 4)
								CObjMgr::GetInst()->AddObj(OBJ_ITEM_PICKUP, CObjFactory<CPickup>::CreateObj((*tileiter)->vPos,PICK_DOUBLEKEY));
							else if(rannum == 5)
								CObjMgr::GetInst()->AddObj(OBJ_ITEM_PICKUP, CObjFactory<CPickup>::CreateObj((*tileiter)->vPos,PICK_KEY));
							else if(rannum == 6)
								CObjMgr::GetInst()->AddObj(OBJ_ITEM_PICKUP, CObjFactory<CPickup>::CreateObj((*tileiter)->vPos,PICK_PENNY));
							else if(rannum == 7)
								CObjMgr::GetInst()->AddObj(OBJ_ITEM_PICKUP, CObjFactory<CPickup>::CreateObj((*tileiter)->vPos,PICK_HEART));
							else if(rannum == 8)
								CObjMgr::GetInst()->AddObj(OBJ_ITEM_PICKUP, CObjFactory<CPickup>::CreateObj((*tileiter)->vPos,PICK_HALFHEART));
							else if(rannum == 9)
								CObjMgr::GetInst()->AddObj(OBJ_ITEM_PICKUP, CObjFactory<CPickup>::CreateObj((*tileiter)->vPos,PICK_DOUBLEHEART));
						}
						else
						{
							//�Ʒ�
							(*tileiter)->byDrawID = 5;
							(*tileiter)->byOption = 0;
							srand(unsigned(time(NULL)));
							(*tileiter)->byOption = 0;
							int rannum = rand()%10;
							if(rannum == 0)
								CObjMgr::GetInst()->AddObj(OBJ_ITEM_PICKUP, CObjFactory<CPickup>::CreateObj((*tileiter)->vPos,PICK_NICKEL));
							else if(rannum == 1)
								CObjMgr::GetInst()->AddObj(OBJ_ITEM_PICKUP, CObjFactory<CPickup>::CreateObj((*tileiter)->vPos,PICK_BOMB));
							else if(rannum == 2)
								CObjMgr::GetInst()->AddObj(OBJ_ITEM_PICKUP, CObjFactory<CPickup>::CreateObj((*tileiter)->vPos,PICK_DIME));
							else if(rannum == 3)
								CObjMgr::GetInst()->AddObj(OBJ_ITEM_PICKUP, CObjFactory<CPickup>::CreateObj((*tileiter)->vPos,PICK_DOUBLEBOMB));
							else if(rannum == 4)
								CObjMgr::GetInst()->AddObj(OBJ_ITEM_PICKUP, CObjFactory<CPickup>::CreateObj((*tileiter)->vPos,PICK_DOUBLEKEY));
							else if(rannum == 5)
								CObjMgr::GetInst()->AddObj(OBJ_ITEM_PICKUP, CObjFactory<CPickup>::CreateObj((*tileiter)->vPos,PICK_KEY));
							else if(rannum == 6)
								CObjMgr::GetInst()->AddObj(OBJ_ITEM_PICKUP, CObjFactory<CPickup>::CreateObj((*tileiter)->vPos,PICK_PENNY));
							else if(rannum == 7)
								CObjMgr::GetInst()->AddObj(OBJ_ITEM_PICKUP, CObjFactory<CPickup>::CreateObj((*tileiter)->vPos,PICK_HEART));
							else if(rannum == 8)
								CObjMgr::GetInst()->AddObj(OBJ_ITEM_PICKUP, CObjFactory<CPickup>::CreateObj((*tileiter)->vPos,PICK_HALFHEART));
							else if(rannum == 9)
								CObjMgr::GetInst()->AddObj(OBJ_ITEM_PICKUP, CObjFactory<CPickup>::CreateObj((*tileiter)->vPos,PICK_DOUBLEHEART));
						}
					}
				}
			}
		}
	}
}
//0. �̵����� 1. �̵��Ұ� 2.���� 3.X 4.�� 
//5.�� 6.�� 7.���� �޹� 8.���� �޹� 9.���� ������ 
//10.���� ������ 11. ���� ���� 12.���� ���� 13.���� �Ʒ��� 14.���� �Ʒ���