// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"
#include "windows.h"
#include <iostream>
#include <vector>
#include <list>


using namespace std;

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
		//OBJ_ID = OBJ_END;
		OBJ_ID = 37;
	}
}PACKET;



typedef struct Key
{
	int clientNum;
	bool key[4];

}KEYDATA;

// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
