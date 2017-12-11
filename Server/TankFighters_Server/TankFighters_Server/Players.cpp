#include "Players.h"



Player::Player()
{
	ZeroMemory(&PlayerMove, sizeof(KEYDATA));

	if (PlayerMove.clientNum == 0)
	{
		Packet.fX = 200.0f;
		Packet.fY = 384.0f;
	}
	else if (PlayerMove.clientNum == 1)
	{
		Packet.fX = 700.0f;
		Packet.fY = 384.0f;
	}
}


Player::~Player()
{
}

void Player::Update(Timer timer)
{
	// 0:상 1:하 2:좌 3:우 ,4 5 6 7: 공격

	//---------->x
	//	|
	//	|
	//	|
	//	|
	//	|
	//	V y

	if (PlayerMove.key[0] == true)
		Move(0,-1,timer);
	if (PlayerMove.key[1] == true)
		Move(0, 1, timer);
	if (PlayerMove.key[2] == true)
		Move(-1, 0, timer);
	if (PlayerMove.key[3] == true)
		Move(1,0, timer);
	
	//if (PlayerMove.key[0] == true)
	//	Move(0, 5);
	//if (PlayerMove.key[0] == true)
	//	Move(0, 5);
	//if (PlayerMove.key[0] == true)
	//	Move(0, 5);
	//if (PlayerMove.key[0] == true)
	//	Move(0, 5);

}