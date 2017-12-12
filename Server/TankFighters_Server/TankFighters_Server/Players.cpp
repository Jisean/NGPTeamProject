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

Player::Player(int iNum)
{
	ZeroMemory(&PlayerMove, sizeof(KEYDATA));

	if (iNum == 0)
	{
		PlayerMove.clientNum = 0;
		Packet.OBJ_ID = ID_PLAYER;
		Packet.fX = 200.0f;
		Packet.fY = 384.0f;
	}
	else if (iNum == 1)
	{
		PlayerMove.clientNum = 1;
		Packet.OBJ_ID = ID_PLAYER2;
		Packet.fX = 700.0f;
		Packet.fY = 384.0f;
	}
}


Player::~Player()
{
}

void Player::Update(Timer timer)
{

	cout << "Player " << PlayerMove.clientNum << " : " << "╩С:" << PlayerMove.key[0] << "го:" << PlayerMove.key[1] << "аб:" << PlayerMove.key[2] << "©Л:" << PlayerMove.key[3] << endl;


	// 0:╩С 1:го 2:аб 3:©Л ,4 5 6 7: ╟Ь╟щ

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