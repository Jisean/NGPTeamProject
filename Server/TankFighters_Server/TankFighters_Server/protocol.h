#pragma once
<<<<<<< HEAD
#include <stdlib.h>
#include <stdio.h>
=======
>>>>>>> origin/master

#define SERVERIP   "127.0.0.1"
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


typedef struct tagPACKET // 패킷
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
<<<<<<< HEAD
=======
		OBJ_ID = OBJ_END;
>>>>>>> origin/master
	}
}PACKET;


typedef struct tagPacket
{
	PACKET	PlayerInfo1; // 플레이어1
	PACKET	PlayerInfo2; // 플레이어2
	PACKET  BulletInfo[30]; // 불렛의 패킷
	UINT	BulletSize;
	UINT	MonsterSize;

}ORIGIN;

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