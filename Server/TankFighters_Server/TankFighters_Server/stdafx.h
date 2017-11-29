// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#include <iostream>
#include <vector>
#include <list>


using namespace std;

typedef struct ObjInfo  //오브젝트 정보 == 공유자원
{
	float posX;
	float posY;
	int hp;
	int state;

}OBJDATA;

typedef struct Key
{
	int clientNum;
	bool key[8];

}KEYDATA;

// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
