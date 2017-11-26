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
	GameStatus = Game::start;
}

void ServerMgr::GameEnd()
{
	GameStatus = Game::end;
}