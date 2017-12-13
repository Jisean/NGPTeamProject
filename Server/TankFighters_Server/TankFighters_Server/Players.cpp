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

	cout << "Player " << PlayerMove.clientNum << " : " << "»ó:" << PlayerMove.key[0] << "ÇÏ:" << PlayerMove.key[1] << "ÁÂ:" << PlayerMove.key[2] << "¿ì:" << PlayerMove.key[3] << endl;
	cout <<  "ÃÑ¾Ë »ó:" << PlayerMove.key[4] << "ÃÑ¾Ë ÇÏ:" << PlayerMove.key[5] << "ÃÑ¾Ë ÁÂ:" << PlayerMove.key[6] << "ÃÑ¾Ë ¿ì:" << PlayerMove.key[7] << endl;


	// 0:»ó 1:ÇÏ 2:ÁÂ 3:¿ì ,4 5 6 7: °ø°Ý

	//---------->x
	//	|
	//	|
	//	|
	//	|
	//	|
	//	V y

	Packet.KeyData = PlayerMove;

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