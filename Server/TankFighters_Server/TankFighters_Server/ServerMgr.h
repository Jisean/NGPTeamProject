#pragma once

#define OBJECT_BULLET 0 
#define OBJECT_TANK 1
#define OBJECT_TILE 2

enum class Game
{
	start = 0,
	end = 1
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

	void Collision();

private:
	Game GameStatus;
	
};

