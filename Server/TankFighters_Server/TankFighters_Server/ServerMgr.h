#pragma once

#include "GameObj.h"
#include "Players.h"
#include "Bullets.h"

#define OBJECT_BULLET 0 
#define OBJECT_TANK 1
#define OBJECT_TILE 2



class ServerMgr
{
public:
	ServerMgr();
	~ServerMgr();

	void GameStart();
	void GameEnd();
	void GameWait();

	void CreateObject(int ObjectType);
	void DeleteObject(int ObjectType);
	void SetKeyData(KEYDATA key);
	
	void Update(Timer timer);
	void UpdatePlayer(KEYDATA key, Timer timer);
	//void Collision();

	int GetGameState() { return GameState; }
	vector<Player> GetPlayers() { return vPlayer; }


	int GameState;  //대기, 게임 시작, 종료를 나타냄(0,1,2)
private:
	//int GameState;  //대기, 게임 시작, 종료를 나타냄(0,1,2)
	
	KEYDATA playerKey[2];

	vector<Player> vPlayer;
	list<Bullets> lBullets;


};

