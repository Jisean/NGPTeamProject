#include "stdafx.h"
#include "ServerMgr.h"


ServerMgr::ServerMgr()
{
	GameState = 0;
}


ServerMgr::~ServerMgr()
{
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

void ServerMgr::UpdatePlayer(KEYDATA key)
{
	int clientNum = key.clientNum;

	vPlayer[clientNum].SetKeyData(key);
	vPlayer[clientNum].Update();


}

void ServerMgr::Update()
{
	for (int i = 0; i < vPlayer.size(); ++i)
		UpdatePlayer(playerKey[i]);



}