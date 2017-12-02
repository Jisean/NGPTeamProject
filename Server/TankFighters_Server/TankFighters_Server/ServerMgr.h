#pragma once

#include "GameObj.h"
#include "Players.h"
#include "Bullets.h"

#define OBJECT_BULLET 0 
#define OBJECT_TANK 1
#define OBJECT_TILE 2

enum class Game
{
	start = 1,
	end = 2,
	wait = 0
};


class ServerMgr
{
public:
	ServerMgr();
	~ServerMgr();

	void GameStart();
	void GameEnd();
	
	void CreateObject(int ObjectType);
	void DeleteObject(int ObjectType);
	void SetKeyData(KEYDATA key);
	
	void Update();
	void UpdatePlayer(KEYDATA key);
	//void Collision();

	Game GetGameState() { return GameState; }
	vector<Player> GetPlayers() { return vPlayer; }



private:
	Game GameState;  //게임 시작, 종료를 나타냄
	
	KEYDATA playerKey[2];

	vector<Player> vPlayer;
	list<Bullets> lBullets;


};

