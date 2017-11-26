#pragma once
class GameObj
{
public:
	GameObj();
	virtual ~GameObj();

	//virtual void Move(int iX, int iY, int client);
	//virtual void DeleteObj(int client);
};

class Player : public GameObj
{


};

class Bullets :public GameObj
{

};

class Tile : public GameObj
{

};