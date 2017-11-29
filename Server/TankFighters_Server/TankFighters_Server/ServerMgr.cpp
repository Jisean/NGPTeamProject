#include "stdafx.h"
#include "ServerMgr.h"


ServerMgr::ServerMgr()
{
}


ServerMgr::~ServerMgr()
{
}

void ServerMgr::GameStart()
{
	GameState = Game::start;
}

void ServerMgr::GameEnd()
{
	GameState = Game::end;
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