#pragma once

#define SERVERPORT 9000
#define BUFSIZE    2048//1024
#define	PURE = 0
#define PI 3.141592


enum OBJ_ID
{
	ID_PLAYER = 0,
	ID_PLAYER2,
	ID_BULLET,
	ID_END
};


typedef struct tagPACKET // ��Ŷ
{
	int OBJ_ID;
	float fX;
	float fY;
	float fCX;
	float fCY;

	int Hp;
	int State;


	tagPACKET()
	{
		fX = 0.f;
		fY = 0.f;
		fCX = 0.f;
		fCY = 0.f;
		Hp = 0.f;
		State = 0.f;
		OBJ_ID = OBJ_END;
	}
}PACKET;


struct ORIGINPACKET
{
	PACKET	PlayerInfo1; // �÷��̾�1
	PACKET	PlayerInfo2; // �÷��̾�2
	PACKET  BulletInfo[30]; // �ҷ��� ��Ŷ
	UINT	BulletSize;
	UINT	MonsterSize;

	SOCKET sock;

	ORIGINPACKET(SOCKET& s) { sock = s; }

};

typedef struct KeyInput
{
	bool	bUp = false;
	bool	bDown = false;
	bool	bLeft = false;
	bool	bRight = false;

	bool	bLShoot = false;
	bool	bRShoot = false;
	bool	bUShoot = false;
	bool	bDShoot = false;
}KEY;



struct SENDPACKET {
	SOCKET sock;
	bool key[4];

	SENDPACKET(SOCKET& s, bool k[4]) { sock = s; for (int i = 0; i < 4; ++i) key[i] = k[i]; }
};