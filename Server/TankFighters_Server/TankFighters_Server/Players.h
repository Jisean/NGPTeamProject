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
	void Update(Timer timer);
	
	KEYDATA GetKeyData(void)
	{
		return PlayerMove;
	}
	void SetKeyData(KEYDATA tPlayerMove)
	{
		PlayerMove = tPlayerMove;
	}
	
};

