#pragma once
#include "stdafx.h"
#include <wtypes.h>

#define SERVERPORT 9000
#define BUFSIZE    2048//1024
#define	PURE = 0
#define PI 3.141592

#include <d3d9.h>
#pragma comment(lib, "d3d9.lib")
#include <d3dx9.h>
#pragma comment(lib, "d3dx9.lib")


const int WINCX = 1024;
const int WINCY = 768;

typedef struct tagInfo
{
	D3DXVECTOR3		vPos;
	D3DXVECTOR3		vLook;
	D3DXVECTOR3		vDir;
	D3DXVECTOR3		vSize;

	D3DXMATRIX		matWorld;

}INFO;




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
		OBJ_ID = ID_END;
	}
}PACKET;

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



struct ORIGINPACKET
{
	PACKET	PlayerInfo1; // �÷��̾�1
	PACKET	PlayerInfo2; // �÷��̾�2
	PACKET  BulletInfo[30]; // �ҷ��� ��Ŷ
	UINT	BulletSize;
	KEY		KeyValue;
};