#pragma once
#include "GameObj.h"

class Player : public GameObj
{
private:
	KEYDATA PlayerMove;
	int hp;

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
	
};

