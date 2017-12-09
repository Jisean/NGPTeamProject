#include "Players.h"



Player::Player()
{
	ZeroMemory(&PlayerMove, sizeof(KEYDATA));
	Packet.fX = 500.0f;
	Packet.fY = 400.0f;
}


Player::~Player()
{
}

void Player::Update()
{
	// 0:위 1:아래 2:좌 3:우 ,4 5 6 7: 공격

	if (PlayerMove.key[0] == true)
		Move(0, 5);
	if (PlayerMove.key[1] == true)
		Move(0, -5);
	if (PlayerMove.key[2] == true)
		Move(-5, 0);
	if (PlayerMove.key[3] == true)
		Move(5, 0);
	
	//if (PlayerMove.key[0] == true)
	//	Move(0, 5);
	//if (PlayerMove.key[0] == true)
	//	Move(0, 5);
	//if (PlayerMove.key[0] == true)
	//	Move(0, 5);
	//if (PlayerMove.key[0] == true)
	//	Move(0, 5);

}