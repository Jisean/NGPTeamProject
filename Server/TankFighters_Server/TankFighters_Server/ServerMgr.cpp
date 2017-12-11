#include "stdafx.h"
#include "ServerMgr.h"


ServerMgr::ServerMgr()
{
	GameState = 0;
}


ServerMgr::~ServerMgr()
{
}

void ServerMgr::GameWait()
{
	GameState = 0;
}
void ServerMgr::GameStart()
{
	GameState = 1;
}

void ServerMgr::GameEnd()
{
	GameState = 2;
}

void ServerMgr::CreateObject(int ObjectType)
{
	if (ObjectType == OBJECT_TANK)
	{
		vPlayer.push_back(Player());
	}
	else if (ObjectType == OBJECT_BULLET)
	{
	}
	else if (ObjectType == OBJECT_TILE)
	{
	}
}

void ServerMgr::DeleteObject(int ObjectType)
{
	if (ObjectType == OBJECT_TANK)
	{
	}
	else if (ObjectType == OBJECT_BULLET)
	{
	}
	else if (ObjectType == OBJECT_TILE)
	{
	}
}


void ServerMgr::SetKeyData(KEYDATA key)
{
	playerKey[key.clientNum] = key;
}

void ServerMgr::UpdatePlayer(KEYDATA keyData, Timer timer)
{
	int clientNum = keyData.clientNum;

	vPlayer[clientNum].SetKeyData(keyData);
	vPlayer[clientNum].Update(timer);

	//ÃÑ¾Ë »ý¼º 
	if (keyData.key[4] || keyData.key[5] || keyData.key[6] || keyData.key[7])
	{
		Bullets tBullet;
		tBullet.SetClient(keyData.clientNum);
		tagPACKET tPacket;
		tPacket.fX = vPlayer[clientNum].GetData().fX;
		tPacket.fY = vPlayer[clientNum].GetData().fY;
		tPacket.State = 1;
		tBullet.SetData(tPacket);

		lBullets.emplace_back(tBullet);
	}
}

void ServerMgr::Update(Timer timer)
{
	for (int i = 0; i < vPlayer.size(); ++i)
		UpdatePlayer(playerKey[i], timer);



}