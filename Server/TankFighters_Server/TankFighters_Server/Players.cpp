#include "Players.h"



Player::Player()
{
	//�÷��̾� ������ �ʱ�ȭ �������
	objData.posX = 0;
	objData.posY = 0;
}


Player::~Player()
{
}


KEYDATA Player::GetKeyData()
{
	return PlayerMove;
}

void Player::Update()
{
	// 0:�� 1:�Ʒ� 2:�� 3:�� ,4 5 6 7: ����

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