#pragma once
#include "GameObj.h"

class Player : public GameObj
{
public:
	Player();
	~Player();

	int GetHp() const { return hp; }
	void Update();
	
	KEYDATA GetKeyData();
	void SetKeyData(KEYDATA tPlayerMove)
	{
		PlayerMove = tPlayerMove;
	}
	
	int GetClientNum()
	{
		return playerNum.clientNum;
	}
	//void SetPlayerNum()
	////{
	//
	//}

private:
	KEYDATA PlayerMove;
	KEYDATA playerNum;
	int hp;
};

